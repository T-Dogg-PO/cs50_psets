/* List titles of all movies that both Johnny Depp and Helena Bonham Carter starred in */
SELECT title FROM
movies JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE name IN ("Johnny Depp", "Helena Bonham Carter")
GROUP BY stars.movie_id
HAVING COUNT(stars.person_id) >= 2;