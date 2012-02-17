
-- create tables
CREATE TABLE weather (
    city            varchar(80),
    temp_lo         int,           -- low temperature
    temp_hi         int,           -- high temperature
    prcp            real,          -- precipitation
    date            date
);

CREATE TABLE cities (
    name            varchar(80),
    --location        point uncomment for postgres
    location        varchar(20)
);


-- insert into weather, cities
INSERT INTO weather VALUES ('San Francisco', 46, 50, 0.25, '1994-11-27');

INSERT INTO cities VALUES ('Petaluma', '(-194.0, 53.0)');
INSERT INTO cities VALUES ('San Francisco', '(-196.0, 54.0)');
INSERT INTO weather VALUES('Petaluma', 50, 62, 1.33, '1994-1-01');

INSERT INTO weather (city, temp_lo, temp_hi, prcp, date)
    VALUES ('Santa Rosa', 43, 57, 0.0, '1994-11-29');

INSERT INTO weather (date, city, temp_hi, temp_lo)
    VALUES ('1994-11-29', 'Hayward', 54, 37);


-- look up all from weather
SELECT * FROM weather;


-- do an average for + edit presentation
SELECT city, (temp_hi+temp_lo)/2 AS temp_avg, date FROM weather;


-- display with two conditions
SELECT * FROM weather
    WHERE city = 'San Francisco'
    AND prcp > 0.24;


--a join query. CON: this query lists city name twice, see next example
SELECT *
    FROM weather, cities
    WHERE city = name;

SELECT city, temp_lo, temp_hi, prcp, date, location
    FROM weather, cities
    WHERE city = name;

-- a more explicit form
SELECT weather.city, weather.temp_lo, weather.temp_hi,
       weather.prcp, weather.date, cities.location
    FROM weather, cities
    WHERE cities.name = weather.city;


-- Inner join...List both that match
SELECT *
    FROM weather INNER JOIN cities ON (weather.city = cities.name);

-- outer join, This query is called a left outer join because the table mentioned on 
-- the left of the join operator will have each of its rows in the output at least once
-- If the entry on the left does not have an index on the right, there will be a 'blank fill'
SELECT *
    FROM weather LEFT OUTER JOIN cities ON (weather.city = cities.name);

--- this does the opposite, for every city in cities, look up the weather
SELECT *
    FROM weather RIGHT OUTER JOIN cities ON (weather.city = cities.name);

--create aliases
SELECT *
    FROM weather w, cities d
    WHERE w.city = d.name;

SELECT city, temp_lo, location
    FROM weather w, cities d
    WHERE w.city = d.name;

-- display two cities where city1 low,high are larger absolutely.
SELECT W1.city, W1.temp_lo AS low, W1.temp_hi AS high,
    W2.city, W2.temp_lo AS low, W2.temp_hi AS high
    FROM weather W1, weather W2
    WHERE W1.temp_lo < W2.temp_lo
    AND W1.temp_hi > W2.temp_hi;


