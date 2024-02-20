-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get reports

SELECT *
FROM crime_scene_reports csr
WHERE "year" = 2021 AND "month" = 7 AND "day" = 28
AND street = 'Humphrey Street'

-- Get interviews

SELECT *
FROM interviews i
WHERE "year" = 2021 AND "month" = 7 AND "day" = 28

-- Get cars

SELECT *
FROM bakery_security_logs bsl
WHERE "year" = 2021 AND "month" = 7 AND "day" = 28
AND "hour" = 10

-- Join ATM transations and bakey logs

SELECT transaction_type , amount, name, phone_number, passport_number, p.license_plate, bsl."year" , bsl."month" , bsl."day", bsl."hour" , bsl."minute"
FROM atm_transactions at2
JOIN bank_accounts ba ON at2.account_number = ba.account_number
JOIN people p ON p.id = ba.person_id
JOIN bakery_security_logs bsl ON p.license_plate = bsl.license_plate
WHERE at2."year" = 2021 AND at2."month" = 7 AND at2."day" = 28
AND at2.atm_location = 'Leggett Street'
AND bsl."day" = 28 and bsl."hour" >= 10
ORDER BY bsl."minute"

-- Narrow down suspects based on phone calls

SELECT caller, receiver, name, passport_number , license_plate
FROM phone_calls pc
JOIN people p
ON pc.caller = p.phone_number
WHERE "year" = 2021 AND "month" = 7 AND "day" = 28
AND duration < 60
AND name in ('Bruce', 'Luca', 'Iman', 'Diana', 'Taylor')

-- Narrow down suspects based on purchase

SELECT name, phone_number, p.passport_number, license_plate
FROM flights f
JOIN passengers p ON f.id = p.flight_id
JOIN people p2 on p.passport_number = p2.passport_number
WHERE "year" = 2021 AND "month" = 7 AND "day" = 29
AND f.id = 36
AND p2.name in ('Bruce', 'Luca', 'Iman', 'Diana', 'Taylor')

-- Get the ACCOMPLICE

SELECT *
FROM people p
WHERE p.phone_number = "(375) 555-8161"

-- Get the destination

SELECT *
FROM flights f
JOIN airports a ON f.destination_airport_id = a.id
WHERE f.id = 36
