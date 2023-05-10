SELECT movies.title
FROM movies, stars, people
WHERE stars.movie_id = movies.id
AND stars.person_id = people.id
AND name = "Johnny Depp"
INTERSECT
SELECT movies.title
FROM movies, stars, people
WHERE stars.movie_id = movies.id
AND stars.person_id = people.id
AND name = "Helena Bonham Carter";
