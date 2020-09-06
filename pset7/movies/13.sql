/* List names of all people who have starred in a movie that also starred Kevin Bacon */
SELECT people.name FROM
people JOIN stars ON people.id = stars.person_id
WHERE people.id IN
(SELECT stars.person_id FROM stars WHERE stars.movie_id IN
(SELECT stars.movie_id FROM stars WHERE stars.person_id IN
(SELECT people.id FROM people WHERE (people.name = "Kevin Bacon" AND people.birth = 1958))))
AND people.name != "Kevin Bacon"
GROUP BY people.name;