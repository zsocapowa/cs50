SELECT title
FROM movies m
JOIN ratings r on m.id = r.movie_id
JOIN stars s on s.movie_id = m.id
JOIN people p ON s.person_id = p.id
WHERE name = 'Chadwick Boseman'
ORDER by rating DESC
LIMIT 5