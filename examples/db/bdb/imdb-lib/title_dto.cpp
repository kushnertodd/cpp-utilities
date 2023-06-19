#include <cstring>
#include <sstream>
#include <utility>
#include "bdb_file_io.hpp"
#include "bdb_json_utils.hpp"
#include "serialization.hpp"
#include "bdb_tokens.hpp"
#include "title_dto.hpp"

const std::string Title_DTO::class_name = "Title_DTO";

Title_DTO::Title_DTO(void *buffer) {
  deserialize(buffer);
}

Title_DTO::Title_DTO(int count, const std::string &line, Bdb_errors &errors, char delimiter) {
  parse(count, line, errors, delimiter);
}

size_t Title_DTO::buffer_size() const {
  size_t len = 0;
  len += Serialization::buffer_len_string(title_id);
  len += Serialization::buffer_len_string(titleType);
  len += Serialization::buffer_len_string(primaryTitle);
  len += Serialization::buffer_len_string(isAdult);
  len += Serialization::buffer_len_string(startYear);
  len += Serialization::buffer_len_string(runtimeMinutes);
  len += Serialization::buffer_len_string(genres);
  return len;
}

void *Title_DTO::deserialize(void *buffer) {
  auto *p = (unsigned char *) buffer;
  p = (unsigned char *) Serialization::deserialize_string(title_id, p);
  p = (unsigned char *) Serialization::deserialize_string(titleType, p);
  p = (unsigned char *) Serialization::deserialize_string(primaryTitle, p);
  p = (unsigned char *) Serialization::deserialize_string(isAdult, p);
  p = (unsigned char *) Serialization::deserialize_string(startYear, p);
  p = (unsigned char *) Serialization::deserialize_string(runtimeMinutes, p);
  p = (unsigned char *) Serialization::deserialize_string(genres, p);
  return p;
}

bool Title_DTO::equals(const Title_DTO &title) const {
  return (title_id == title.title_id
      && titleType == title.titleType
      && primaryTitle == title.primaryTitle
      && isAdult == title.isAdult
      && startYear == title.startYear
      && runtimeMinutes == title.runtimeMinutes
      && averageRating == title.averageRating
      && numVotes == title.numVotes
      && genres == title.genres);
}

void Title_DTO::from_json(json_object *jobj, Bdb_errors &errors) {
  // parse: ' { "class_name": ... `
  std::string jobj_class_name =
      Bdb_json_utils::get_json_string("Title_DTO::from_json", "1", jobj, "class_name", errors);
  if (!errors.has() && jobj_class_name != class_name)
    errors.add("Title_DTO::from_json", "2", "not class Title_DTO");
  // parse: ' { "title_id": ... `
  title_id = Bdb_json_utils::get_json_string("Title_DTO::from_json", "1", jobj, "title_id", errors);
  if (!errors.has())
    // parse: ' { titleType": ... `
    titleType = Bdb_json_utils::get_json_string("Title_DTO::from_json", "2", jobj, "titleType", errors);
  if (!errors.has())
    // parse: ' { "primaryTitle": ... `
    primaryTitle = Bdb_json_utils::get_json_string("Title_DTO::from_json", "3", jobj, "primaryTitle", errors);
  if (!errors.has())
    // parse: ' { "isAdult": ... `
    isAdult = Bdb_json_utils::get_json_string("Title_DTO::from_json", "4", jobj, "isAdult", errors);
  if (!errors.has())
    // parse: ' { "startYear": ... `
    startYear = Bdb_json_utils::get_json_string("Title_DTO::from_json", "5", jobj, "startYear", errors);
  if (!errors.has())
    // parse: ' { "runtimeMinutes": ... `
    runtimeMinutes = Bdb_json_utils::get_json_string("Title_DTO::from_json", "6", jobj, "runtimeMinutes", errors);
  if (!errors.has())
    // parse: ' { "genres": ... `
    genres = Bdb_json_utils::get_json_string("Title_DTO::from_json", "7", jobj, "genres", errors);
}

int Title_DTO::get_title_primary_name(Db *dbp, const Dbt *pkey, const Dbt *pdata, Dbt *skey) {
  Bdb_errors errors;
  Title_DTO title_dto(pdata->get_data());
  // key memory is malloc()'d, berkeley db will free
  std::memset((void *) skey, 0, sizeof(Dbt));
  skey->set_flags(DB_DBT_APPMALLOC);
  std::string title_primaryTitle = title_dto.primaryTitle;
  size_t keylen = title_primaryTitle.size() + 1;
  char *title_primaryTitle_buf = (char *) malloc(keylen);
  strcpy(title_primaryTitle_buf, title_primaryTitle.c_str());
  // Now set the secondary key's data to be the primaryTitle
  skey->set_data(title_primaryTitle_buf);
  skey->set_size(keylen);
  return (0);
}

void Title_DTO::parse(int count, const std::string &line, Bdb_errors &errors, char delimiter) {
  // tconst	titleType	primaryTitle	originalTitle	isAdult	startYear	endYear	runtimeMinutes	genres
  std::vector<std::string> token_list = Bdb_Tokens::tokenize(line, '\t');
  int i = 0;
  for (const std::string &token_str: token_list) {
    switch (i) {
      case 0: {
        title_id = token_str;
        if (title_id == "\\N")
          errors.add("Title_DTO::create", "1", "required title_id == '\\N'");
        break;
      }
      case 1: {
        titleType = token_str;
        if (titleType == "\\N")
          errors.add("Title_DTO::create", "2", "required titleType == '\\N'");
        break;
      }
      case 2: {
        primaryTitle = token_str;
        if (primaryTitle == "\\N")
          errors.add("Title_DTO::create", "3", "required primaryTitle == '\\N'");
        break;
      }
      case 3: {
        break;
      }
      case 4: {
        isAdult = token_str;
        // TODO: required?
        if (isAdult == "\\N")
          errors.add("Title_DTO::create", "4", "required isAdult == '\\N'");
        break;
      }
      case 5: {
        startYear = (token_str == "\\N" ? "" : token_str);
        break;
      }
      case 6: {
        break;
      }
      case 7: {
        runtimeMinutes = (token_str == "\\N" ? "" : token_str);
        break;
      }
      case 8: {
        genres = (token_str == "\\N" ? "" : token_str);
        break;
      }
      default: {
        errors.add("Title_DTO::create", "5", "too many title fields on line "
            + Bdb_Tokens::line_print(count, line));
      }
    }
    i++;
  }
  // Store the tokens as per structure members , where (i==0) is first member and so on..
  if (i != 9) {
    errors.add("Title_DTO::create", "6", "too few name fields on line"
        + Bdb_Tokens::line_print(count, line));
  }
}

void *Title_DTO::serialize(void *buffer) const {
  auto *p = (unsigned char *) buffer;
  p = (unsigned char *) Serialization::serialize_string(title_id, p);
  p = (unsigned char *) Serialization::serialize_string(titleType, p);
  p = (unsigned char *) Serialization::serialize_string(primaryTitle, p);
  p = (unsigned char *) Serialization::serialize_string(isAdult, p);
  p = (unsigned char *) Serialization::serialize_string(startYear, p);
  p = (unsigned char *) Serialization::serialize_string(runtimeMinutes, p);
  p = (unsigned char *) Serialization::serialize_string(genres, p);
  return p;
}

json_object *Title_DTO::to_json(Bdb_errors &errors) const {
  json_object *root = json_object_new_object();
  if (!root) {
    errors.add("Title_DTO::to_json", "1", "json-c allocate error");
    return nullptr;
  }
  json_object_object_add(root, "class_name", json_object_new_string(class_name.c_str()));
  json_object_object_add(root, "title_id", json_object_new_string(title_id.c_str()));
  json_object_object_add(root, "titleType", json_object_new_string(titleType.c_str()));
  json_object_object_add(root, "primaryTitle", json_object_new_string(primaryTitle.c_str()));
  json_object_object_add(root, "isAdult", json_object_new_string(isAdult.c_str()));
  json_object_object_add(root, "startYear", json_object_new_string(startYear.c_str()));
  json_object_object_add(root, "runtimeMinutes", json_object_new_string(runtimeMinutes.c_str()));
  json_object_object_add(root, "genres", json_object_new_string(genres.c_str()));
  return root;
}

std::string Title_DTO::to_string() const {
  std::ostringstream os;
  os << "title:" << std::endl;
  os << "\ttitle_id        " << title_id << std::endl;
  os << "\ttitleType       " << titleType << std::endl;
  os << "\tprimaryTitle    " << primaryTitle << std::endl;
  os << "\tisAdult         " << isAdult << std::endl;
  os << "\tstartYear       " << startYear << std::endl;
  os << "\truntimeMinutes  " << runtimeMinutes << std::endl;
  os << "\tgenres          " << genres << std::endl;
  return os.str();
}

Title_DTO_key::Title_DTO_key(const Title_DTO &title_dto) : title_id(title_dto.title_id) {
}

Title_DTO_key::Title_DTO_key(const Principals_DTO &principals_dto) : title_id(principals_dto.title_id) {
}

Title_DTO_key::Title_DTO_key(std::string title_id_) : title_id(std::move(title_id_)) {
}

Title_DTO_key::Title_DTO_key(void *buffer) {
  deserialize(buffer);
}

size_t Title_DTO_key::buffer_size() const {
  size_t len = 0;
  len += Serialization::buffer_len_string(title_id);
  return len;
}

void *Title_DTO_key::deserialize(void *buffer) {
  auto *p = (unsigned char *) buffer;
  p = (unsigned char *) Serialization::deserialize_string(title_id, p);
  return p;
}

void *Title_DTO_key::serialize(void *buffer) const {
  auto *p = (unsigned char *) buffer;
  p = (unsigned char *) Serialization::serialize_string(title_id, p);
  return p;
}

std::string Title_DTO_key::to_string() const {
  return "title_id: " + title_id;
}

const std::string Title_DTO_list::class_name = "Title_DTO_list";

json_object *Title_DTO_list::to_json(Bdb_errors &errors) const {
  json_object *root = json_object_new_object();
  if (!root) {
    errors.add("Primary_database_config::to_json", "1", "json-c allocate error");
    return nullptr;
  }
  json_object_object_add(root, "class_name", json_object_new_string(class_name.c_str()));
  if (!errors.has() && !list.empty()) {
    json_object *title_dto_list_json = json_object_new_array();
    json_object_object_add(root, "title_dto_list", title_dto_list_json);
    for (const auto &title_dto: list) {
      json_object *title_dto_json = title_dto.to_json(errors);
      if (errors.has())
        break;
      json_object_array_add(title_dto_list_json, title_dto_json);
    }
  }
  if (!errors.has()) {
    return root;
  } else {
    json_object_put(root);
    return nullptr;
  }
}
