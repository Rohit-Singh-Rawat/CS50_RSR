SELECT DISTINCT(name)
FROM stars, people
WHERE movie_id
IN (
    SELECT movies.id
    FROM movies, stars, people
    WHERE stars.movie_id = movies.id
    AND stars.person_id = people.id
    AND name = "Kevin Bacon"
    AND people.birth = 1958
    )
AND stars.person_id = people.id
AND name != "Kevin Bacon";