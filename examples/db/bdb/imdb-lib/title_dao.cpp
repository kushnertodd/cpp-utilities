#include "imdb_dao.hpp"
#include "ratings_dto.hpp"
#include "title_dao.hpp"
#include "title_dto.hpp"

int Title_DAO::load(Bdb_db &title_db, const std::string &text_file, Bdb_errors &errors, char delimiter) {
  return Bdb_DAO<Title_DTO, Title_DTO_key>::load(title_db, text_file, errors, delimiter);
}

void Title_DAO::lookup(Bdb_db &title_db, const std::string &title_id, Title_DTO &title_dto, Bdb_errors &errors) {
  Title_DTO_key title_DTO_key(title_id);
  Bdb_DAO<Title_DTO, Title_DTO_key>::lookup(title_db, title_dto, title_DTO_key, errors);
  Ratings_DTO ratings_dto;
  if (!errors.has())
    Bdb_DAO<Ratings_DTO, Title_DTO_key>::lookup(title_db, ratings_dto, title_DTO_key, errors);
  if (!errors.has()) {
    title_dto.averageRating = ratings_dto.averageRating;
    title_dto.numVotes = ratings_dto.numVotes;
  }
}

void Title_DAO::save(Bdb_db &title_db, Title_DTO &title_dto, Bdb_errors &errors) {
  Bdb_DAO<Title_DTO, Title_DTO_key>::save(title_db, title_dto, errors);
}

void Title_DAO_list::select(Bdb_db &title_db, Title_DTO_list &title_dto_list, Bdb_errors &errors) {
  Bdb_DAO_list<Title_DTO_key, Title_DTO_list>::select(title_db, title_dto_list, errors);
}
