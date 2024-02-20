SELECT name
FROM stars s
JOIN people p2 ON s.person_id = p2.id
WHERE movie_id IN (
    SELECT m.id
    FROM movies m
    JOIN stars s ON s.movie_id = m.id
    JOIN people p ON s.person_id = p.id
    WHERE p.name = 'Kevin Bacon' AND p.birth = 1958
)
AND name != 'Kevin Bacon'