import re
text = input("Text: ")
words = text.split()  # spliting text into words.
lines = re.split(r"[.!?]", text)  # spliting text into part at (.,!,?).
letters_count = 0
for i in text:  # Counting letters in text.
    if i.isalpha():
        letters_count += 1
L = float(letters_count / len(words)) * 100  # Average number of letters per 100 words in the text.
S = float((len(lines) - 1) / len(words)) * 100  # Average number of sentences per 100 words in the text.
Grade = round(0.0588 * L - 0.296 * S - 15.8)  # Coleman-Liau index formula.
if Grade < 1:  # If Grade less than 1.
    print("Before Grade 1")
elif Grade > 16:  # If Grade is more than 16.
    print("Grade 16+")
else:  # If Grade is between 1 and 16 (including them).
    print(f" Grade {Grade}")