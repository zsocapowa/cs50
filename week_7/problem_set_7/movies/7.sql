SELECT title, rating
FROM ratings r
JOIN movies m
ON r.movie_id = m.id
WHERE "year" = 2010
ORDER BY rating DESC, title ASC