CREATE TABLE readers (
    reader_num SERIAL PRIMARY KEY,
    reader_name VARCHAR(100) NOT NULL,
    reader_address VARCHAR(100),
    reader_phone VARCHAR(100) NOT NULL UNIQUE
);

CREATE TABLE book_types (
    type_id SERIAL PRIMARY KEY,
    type_name VARCHAR(100) NOT NULL
);

CREATE TABLE books (
    book_num SERIAL,
    book_author VARCHAR(100),
    book_name VARCHAR(100),
    book_count INTEGER NOT NULL DEFAULT 0,
    type_id INTEGER,
    PRIMARY KEY(book_num),
    FOREIGN KEY(type_id) REFERENCES book_types(type_id)
);

CREATE TABLE books_in_use (
    book_in_use_num SERIAL,
    reader_num INTEGER,
    book_num INTEGER,
    issue_date DATE,
    return_date DATE,
    return_period INTEGER NOT NULL DEFAULT 15,
    PRIMARY KEY(book_in_use_num),
    UNIQUE (reader_num, book_num, issue_date),
    FOREIGN KEY(reader_num) REFERENCES readers(reader_num),
    FOREIGN KEY(book_num) REFERENCES books(book_num)
);