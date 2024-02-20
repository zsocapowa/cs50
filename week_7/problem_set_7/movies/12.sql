SELECT title
FROM movies m
JOIN stars s on s.movie_id = m.id
JOIN people p ON s.person_id = p.id
WHERE name = 'Bradley Cooper' or name = 'Jennifer Lawrence'
GROUP BY title
HAVING COUNT(*) > 1