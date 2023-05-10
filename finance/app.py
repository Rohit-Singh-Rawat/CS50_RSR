import os

from datetime import datetime, date
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", session["user_id"])
    TOTAL = 0
    for stock in stocks:
        price = lookup(stock["symbol"])["price"]
        total = price * stock["shares"]
        TOTAL += total
        stock |= {"price" : format(round(price, 2), '.2f'), "total": format(round(total, 2), '.2f')}
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0]["cash"]
    TOTAL += cash

    return render_template("index.html", stocks=stocks, cash=format(round(cash, 2), '.2f'),\
         TOTAL=format(round(TOTAL, 2), '.2f'))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        sym_dic = lookup(symbol)

        if sym_dic != None:
            if shares.isdigit() == False:
                return apology("Invalid input",400)
            else:
                if int(shares) <= 0:
                    return apology("Invalid number of shares", 400)
                else:
                    name = sym_dic["name"]
                    user_id = session["user_id"]
                    price = sym_dic["price"]
                    D_T = datetime.now()
                    D_T = str(D_T.strftime("%d/%m/%Y %H:%M:%S"))
                    user = db.execute("SELECT cash FROM users where id = ?", user_id)
                    db.execute("UPDATE users SET cash = ? WHERE id = ?",\
                         user[0]["cash"] - (price * float(shares)), user_id)
                    db.execute("INSERT INTO transition(user_id, symbol, shares, price, Transacted)\
                         VALUES(?,?,?,?,?)", user_id, symbol, shares, price, D_T)
                    try:
                        db.execute("INSERT INTO stocks(user_id, symbol, name, shares) VALUES(?,?,?,?)", user_id, symbol, name, shares)
                    except:
                        shares_old = db.execute("SELECT shares FROM stocks WHERE symbol = ? and user_id = ?",\
                             symbol, user_id)
                        db.execute("UPDATE  stocks SET shares = ? WHERE user_id = ? AND symbol = ? ",\
                             shares_old[0]["shares"] + int(shares), user_id, symbol)
                    return redirect("/")
        else:
            return apology("invalid symbol", 400)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transition = db.execute("SELECT * FROM transition WHERE user_id = ?", session["user_id"])
    return render_template("history.html", transitions=transition)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if lookup(symbol) != None:
            sym_dic = lookup(symbol)
            name = sym_dic["name"]
            Symbol = sym_dic["symbol"]
            price = sym_dic["price"]
            return render_template("quoted.html", price=format(round(price, 2), '.2f'), symbol=Symbol, name=name)
        else:
            return apology("invalid symbol", 400)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        password2 = request.form.get("confirmation")
        if not username:
            return apology("user name can't be empty", 400)
        else:
            if password != password2 or password == "":
                return apology("password Invalid!", 400)
            else:
                hash_pass = generate_password_hash(password, method='pbkdf2:sha256', salt_length=16)
                try:
                    db.execute("INSERT INTO users(username, hash) VALUES(?,?)", username, hash_pass)
                    return redirect("/")
                except:
                    return apology("Username not available", 400)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        symbols = db.execute("SELECT symbol FROM stocks WHERE user_id = ? ", session["user_id"])
        return render_template("sell.html", symbols=symbols)
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        share = request.form.get("shares")
        shares = db.execute("SELECT shares FROM stocks WHERE symbol = ? and user_id = ?", symbol, session["user_id"])
        if shares[0]["shares"] != None:
            if share.isdigit() == False:
                return apology("Invalid input", 400)
            else:

                if int(share) <= 0:
                    return apology("Invalid number of shares", 400)
                elif shares[0]["shares"] >= int(share):
                    sym_dic = lookup(symbol)
                    if sym_dic != None:
                        name = sym_dic["name"]
                        user_id = session["user_id"]
                        price = sym_dic["price"]
                        D_T = datetime.now()
                        D_T = str(D_T.strftime("%d/%m/%Y %H:%M:%S"))
                        user = db.execute("SELECT cash FROM users where id = ?", user_id)
                        db.execute("UPDATE users SET cash = ? WHERE id = ?", user[0]["cash"] + (price * float(share)), user_id)
                        db.execute("INSERT INTO transition(user_id, symbol, shares, price, Transacted) VALUES(?,?,?,?,?)", user_id, symbol, -int(share), price, D_T)
                        db.execute("UPDATE  stocks SET shares = ? WHERE user_id = ? AND symbol = ? ", shares[0]["shares"] - int(share), user_id, symbol)
                        shares_new = db.execute("SELECT shares FROM stocks WHERE symbol = ? and user_id = ?",symbol, session["user_id"])

                        if shares_new[0]["shares"] == 0:
                            db.execute("DELETE FROM stocks WHERE symbol = ? and user_id = ?", symbol, session["user_id"])
                        return redirect("/")
                else:
                    return apology("Too many shares", 400)

        else:
            return apology("share can't be found", 400)

