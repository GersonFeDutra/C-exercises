#ifndef LOCALES
#define LOCALES
#define LINE "--------------------"

extern const char *inexistent_list_message;
extern const char *insert_success_message;
extern const char *ok_access_message;
extern const char *not_ok_access_message;
extern const char *error_empty_list_message;
extern const char *input_error_negative_index_message;
extern const char *list_empty_message;
extern const char *list_not_empty_message;
extern const char *null_list_message;
extern const char *clear_list_message;
extern const char *student_message;
extern const char *access_student_message;

extern const char *no_memory_error_message;

enum LOC { DEF, EN, PT };
extern enum LOC loc;

/* load locales based on the language set */
void load_locales(enum LOC);

#endif
