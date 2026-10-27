-- ----------------------------------------------------------------------------
-- Create all tables in PostgreSQL flavour
--
-- modified: 2026-10-27 Harald Braeuning
-- ----------------------------------------------------------------------------



--
-- Table of cameras
--
DROP TABLE IF EXISTS Cameras CASCADE;
CREATE TABLE Cameras (
  id SERIAL PRIMARY KEY,
  model VARCHAR(128) UNIQUE NOT NULL,
  width INTEGER,
  height INTEGER,
  pixelwidth REAL,
  pixelheight REAL,
  sensorwidth REAL,
  sensorheight REAL,
  bpp INTEGER
);

--
-- Table of objects
--
DROP TABLE IF EXISTS Objects CASCADE;
CREATE TABLE Objects (
  id SERIAL PRIMARY KEY,
  name VARCHAR(128) UNIQUE NOT NULL
);

--
-- Table of observers
--
DROP TABLE IF EXISTS Observers CASCADE;
CREATE TABLE Observers (
  id SERIAL PRIMARY KEY,
  name VARCHAR(128) UNIQUE NOT NULL
);

--
-- Table of telescopes
--
DROP TABLE IF EXISTS Telescopes CASCADE;
CREATE TABLE Telescopes (
  id SERIAL PRIMARY KEY,
  model VARCHAR(128) UNIQUE NOT NULL,
  focallength REAL,
  aperture REAL
);

--
-- Table of info snippets
--
DROP TABLE IF EXISTS InfoSnippets CASCADE;
CREATE TABLE InfoSnippets (
  id SERIAL PRIMARY KEY,
  key VARCHAR(128) UNIQUE NOT NULL,
  context VARCHAR(128) UNIQUE NOT NULL,
  note TEXT
);

