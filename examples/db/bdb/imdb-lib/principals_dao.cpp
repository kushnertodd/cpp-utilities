#include "imdb_dao.hpp"
#include "name_dto.hpp"
#include "principals_dto.hpp"
#include "title_dto.hpp"
#include "principals_dao.hpp"

int Principals_DAO::load(Bdb_db &principals_db, const std::string &text_file, Bdb_Errors &errors, char delimiter) {
  return Imdb_DAO<Principals_DTO, Principals_DTO_key>::load(principals_db, text_file, errors, delimiter);
}

void Principals_DAO::lookup(Bdb_db &principals_db,
                            const std::string &principals_id,
                            Principals_DTO &principals_dto,
                            Bdb_Errors &errors) {
  Principals_DTO_key principals_DTO_key(principals_id);
  Imdb_DAO<Principals_DTO, Principals_DTO_key>::lookup(principals_db, principals_dto, principals_DTO_key, errors);
}

void Principals_DAO::save(Bdb_db &principals_db, Principals_DTO &principals_dto, Bdb_Errors &errors) {
  Imdb_DAO<Principals_DTO, Principals_DTO_key>::save(principals_db, principals_dto, errors);
}

void Principals_DAO_list::select(Bdb_db &principals_db, Principals_DTO_list &principals_dto_list, Bdb_Errors &errors) {
  Imdb_DAO_list<Principals_DTO_key, Principals_DTO_list>::select(principals_db, principals_dto_list, errors);
}

void Principals_DAO_list::search_by_name(Bdb_db &title_db,
                                         Bdb_db &principals_db,
                                         Bdb_db &principals_name_id_sdb,
                                         const std::string &name_id,
                                         Title_DTO_list &title_dto_list,
                                         Bdb_Errors &errors) {
  Name_DTO_key name_dto_key(name_id);
  Imdb_DAO_search<Name_DTO_key, Title_DTO, Title_DTO_key, Title_DTO_list>::search(title_db,
                                                                                  principals_db,
                                                                                  principals_name_id_sdb,
                                                                                  name_dto_key,
                                                                                  title_dto_list,
                                                                                  errors);
}

void Principals_DAO_list::search_by_title(Bdb_db &name_db,
                                          Bdb_db &principals_db,
                                          Bdb_db &principals_title_id_sdb,
                                          const std::string &title_id,
                                          Name_DTO_list &name_dto_list,
                                          Bdb_Errors &errors) {
  Title_DTO_key title_dto_key(title_id);
  Imdb_DAO_search<Title_DTO_key, Name_DTO, Name_DTO_key, Name_DTO_list>::search(name_db,
                                                                                principals_db,
                                                                                principals_title_id_sdb,
                                                                                title_dto_key,
                                                                                name_dto_list,
                                                                                errors);
}

template<
    typename K,
    typename R,
    typename S,
    typename L>
class Bdb_DAO_search {
 public:
  static void search(Bdb_db &imdb_db,
                     Bdb_db &principals_db,
                     Bdb_db &imdb_sdb,
                     K &imdb_key,
                     L &imdb_dto_list,
                     Bdb_errors &errors) {
    Dbc *cursorp;
    void *key_buf;
    try {
      int ret = imdb_sdb.get_db().cursor(nullptr, &cursorp, 0);
      if (ret)
        errors.add("Imdbs::select_all_by_datetime", "1", "error creating cursor", ret);
      if (!errors.has()) {
        // Position the cursor to the first record in the secondary database that has the appropriate key.
        size_t key_len = imdb_key.buffer_size();
        key_buf = std::malloc(key_len);
        std::memset(key_buf, '\0', key_len);
        imdb_key.serialize(key_buf);

        Dbt key(key_buf, (u_int32_t) key_len);
        Dbt data;
        for (ret = cursorp->get(&key, &data, DB_SET);
             !ret && !errors.has();
             ret = cursorp->get(&key, &data, DB_NEXT_DUP)) {
          Principals_DTO principals_lookup_dto;
          Principals_DTO_key principals_lookup_key(data.get_data());
          Bdb_DAO<Principals_DTO, Principals_DTO_key>::lookup(principals_db,
                                                              principals_lookup_dto,
                                                              principals_lookup_key,
                                                              errors);
          if (!errors.has()) {
            R imdb_lookup_dto;
            S imdb_lookup_key(principals_lookup_dto);
            Bdb_DAO<R, S>::lookup(imdb_db,
                                  imdb_lookup_dto,
                                  imdb_lookup_key,
                                  errors);
            if (!errors.has())
              imdb_dto_list.list.emplace_back(imdb_lookup_dto);
          }
        }
        if (ret && ret != DB_NOTFOUND) {
          errors.add("Bdb_DAO<T, K>::search", "2", imdb_key.to_string() + " search error: ", ret);
        }
        cursorp->close();
      }
    }
    catch (DbException &e) {
      errors.add("Bdb_DAO<T, K>::search", "3", imdb_key.to_string() + " search error: " + std::string(e.what()));
    }
    catch (std::exception &e) {
      errors.add("Bdb_DAO<T, K>::search", "4", imdb_key.to_string() + " search error: " + std::string(e.what()));
    }
    free(key_buf);
  }
};
