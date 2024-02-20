SELECT DISTINCT(name)
FROM movies m
JOIN ratings r on m.id = r.movie_id
JOIN directors d on d.movie_id = m.id
JOIN people p ON d.person_id = p.id
WHERE rating >= 9