/* Output the average rating of all movies released in 2012 */
SELECT AVG(rating) AS "Average rating of movies releases in 2012:"
FROM ratings JOIN movies ON ratings.movie_id = movies.id
WHERE year = 2012;