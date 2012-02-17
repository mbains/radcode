--get all entries
SELECT polls_entry.id, polls_entry.blog_id, polls_entry.headline FROM polls_entry;


--get authors for polls_entry.id = 1
SELECT
    polls_author.name as 'authors with entries'
    FROM polls_author INNER JOIN polls_entry_authors ON (polls_author.id = polls_entry_authors.author_id)
WHERE polls_entry_authors.entry_id = 1;

--get authors for headline='entrybybob'
SELECT
    polls_author.name as 'authors'
    FROM polls_author INNER JOIN polls_entry_authors ON (polls_author.id = polls_entry_authors.author_id)
    INNER JOIN polls_entry a ON (polls_entry_authors.entry_id = a.id)
WHERE a.headline = 'entrybybob';

--get entries for author = mary'd id
SELECT
    polls_entry.headline
    FROM polls_entry INNER JOIN polls_entry_authors ON (polls_entry.id = polls_entry_authors.entry_id)
WHERE polls_entry_authors.author_id = 2;

--get entries by author's name
SELECT
    polls_entry.headline
    FROM polls_entry INNER JOIN polls_entry_authors ON (polls_entry.id = polls_entry_authors.entry_id)
    INNER JOIN polls_author a ON (a.id = polls_entry_authors.author_id)
WHERE a.`name` = 'mary';

