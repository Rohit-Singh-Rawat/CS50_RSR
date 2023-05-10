-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get description and id of crime on that 7th july at Humphrey Street.

select description,id from crime_scene_reports where month = 7 and day = 28 and street = "Humphrey Street";

-- Id is 295.

-- Reading all interviews of three witnesses who mentioned bakery in thier transcripts.

select * from interviews where year = 2021 and month = 7 and day = 28 and transcript like "%bakery%";

-- Reading all logs of bakery at the time of robbery.(As one witness the thief going out of bakery's parking lot)

select * from bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute >= 15 AND minute <= 25;

-- Reading all atm transactions on the day of theft and at leggett street (as mentioned by one witness.)

select * from atm_transactions where year = 2021 and month = 7 and day = 28 AND transaction_type = "withdraw" and atm_location = "Leggett Street";

-- Reading all phone logs of 28th july 2021 that are less than a minute (also mentioned by witness).

select * from phone_calls where year = 2021 and month = 7 and day = 28 AND duration < 60;

-- Getting id of Fiftyville's airport.

select id from airports where city = "Fiftyville";

-- Getting details of earliest flight from fiftyville on next day of robbery that is  29th july 2021.

select * from flights where origin_airport_id = 8 and year = 2021 and month = 7 and day = 29 order by hour, minute limit 1;

-- Getting thief name who is common in atm_transiction log, parking lot log, phone log, flight's passenger list.

select name from people where id in
(select person_id from bank_accounts where account_number IN (select account_number from atm_transactions where year = 2021 and month = 7 and day = 28 AND transaction_type = "withdraw" and atm_location = "Leggett Street")
intersect
select id from people where phone_number in (select caller from phone_calls where year = 2021 and month = 7 and day = 28 AND duration < 60)
intersect
select id from people where license_plate in (select license_plate from bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute >= 15 AND minute <= 25)
intersect
select id from people where passport_number in (select passport_number from passengers where flight_id = 36));

-- Getting details of Bruce (thief)

select * from people where name = "Bruce";

-- Getting flight's details (To get destination airport id)

select * from flights where id = 36;

-- Getting airport's detail like city and airport name

select * from airports where id = 4;

-- Getting phone log of thief to find his/her partner.

select * from phone_calls where caller = "(367) 555-5533" and year = 2021 and month = 7 and day = 28 AND duration < 60;

-- Getting name of theif's partner using his phone number

select name from people where phone_number = "(375) 555-8161";

