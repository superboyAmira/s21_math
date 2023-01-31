>>> В этом файле я кратко опишу по пунктам что нам нужно для написания UNIT тестов на школьном маке.

>>> Обязательные темы для изучения: 
	1. gcov
	2. lcov
	3. Принципы написания юнит тестов
	4. Фреймфорк Check
* Все полезные ссылки которые я находил и из которых черпал информацию я добавил в свой Notion (ссылку скину)

------
 
>>> Для начала нам нужно установить Homebrew для загрузки пакетов lcov. (Есть ссылка в ноушене)
если нет библиотеки check ее тоже установить.

>>> Написать тесты в отдельном .с файле

=Структура тестов



1. Написание самого теста
Синтаксис таков:

START_TEST(test_name) {
    // Arrange Ввод переменных для тестирования
    Roots* roots =  (Roots*)malloc(sizeof(Roots*));
    double num = 1.0;
    // Act вызов нашей функции и получение результата
    get_roots(num, roots);
    // Assert Сравнение и анализ поведения нашей функции
    ck_assert_double_eq(roots->result_num, 0.0);
    ck_assert_int_eq(roots->isRootExist, TRUE);
    free(roots);
} END_TEST

Тут мы использовали структуру Roots для хранения данных, которые мы получаем от нашей проверяемой функции:

typedef struct Roots {
    double result_num;
    int isRootExist;
} Roots;

А get_roots как раз и является вызовом и распределением нашей полученной информации от функции:

void get_roots(double num, Roots * result) {
    long double func_return = function(num);
    if (num == INF || num == NAN) {
        result->isRootExist = FALSE;
    } else {
        result->result_num = func_return;
        result->isRootExist = TRUE;
    }
}

!!! В НАШЕЙ РАБОТЕ МЫ СОВМЕЩАЕМ Act с Assert, ИЗ-ЗА РАЗЕМРА ПОЛУЧЕННОГО КОДА.

<ck_assert> функция тестирования, которая может принимать большое количество видов, смотря что и как вам нужно проверить 
(Брал отсюда: https://libcheck.github.io/check/doc/check_html/check_4.html)
Например:

ck_assert - Для этого требуется один логический аргумент, который должен быть равен True, чтобы проверка прошла успешно.
ck_assert(strcmp(money_currency(m),"USD") == 0);

ck_assert_int_eq - Два аргумента типа (int) должны быть равны для успешного теста(eq - эквивалентны).
ck_assert_str_eq
ck_assert_double_eq_tol(X, Y, T) - X – число с плавающей запятой
                          Y – число с плавающей запятой для сравнения с X
                          T – точность

ck_assert_msg - Чтобы напечатать определяемое пользователем сообщение вместе с любыми обнаруженными сбоями.

ck_assert_msg(strcmp (money_currency(m), "USD") == 0,
         "Ожидал валюту USD, но нашел %s", money_currency (m));

И т.п.



2. Написание набора (Suite) тестов

Чтобы соединить множество тестов в один исполняемый набор нам нужно написать примерно такой код:

Suite *suite_func_name() {
	Suite *name_suite = suite_create("Name"); // создаем набор
	TCase *name_tcase = tcase_create("Name"); // создаем Кейс для тестов

	tcase_add_test(name_tcase, name_test); // добавляем тест в Кейс
	suite_add_tcase(name_suite, name_tcase); // добавляем кейс в набор 
	return name_suite;
}



3. Main 

Тесты написаны, теперь разберемся как их запустить и использовать.
В "Майне" пишем такой код:

int main() {
  Suite *our_suite = suite_func_name(); // инициализируем и подключаем наш набор тестов
  SRunner *runner = srunner_create(our_suite); // инициализируем раннер, который пробегается по всему набору
  int number_failed = 0; // количество ошибок
  srunner_run_all(runner, CK_VERBOSE); // запускаем раннер
  number_failed = srunner_ntests_failed(runner); // забираем количество ошибок из раннера
  srunner_free(s21_math_runner);

  return number_failed == 0 ? 0 : 1; // будьте аккуратны! Я 4 часа ловил ошибку))) если тесты будут проходить не все - 
									gcov будет ругаться и пропустит дальше и покрытие тестов вы никак не посмотрите! 
									Будет выдавать такую ошибку make: *** [test] Error 1
     https://stackoverflow-com.translate.goog/questions/5535548/make-error-1-error?_x_tr_sl=en&_x_tr_tl=ru&_x_tr_hl=ru&_x_tr_pto=sc
}

Немного про раннер:

Раннер имеет небольшое количество параметров srunner_run_all(runner, CK_VERBOSE)
Вот расшифровка некоторых из них:
https://libcheck.github.io/check/doc/check_html/check_3.html (взято отсюда)


CK_VERBOSE - выводит сообщения о прохождении тестов

CK_SILENT - без вывода сообщений, отчет о тестах можно вести с помощью журнала тестирования https://libcheck.github.io/check/doc/check_html/check_4.html#Test-Logging

CK_MINIMAL - Будет напечатана только сводка по тестовому запуску (Номер запуска, Успех, Сбой, ошибки)

CK_NORMAL - Выводит сводку выполнения и выводит по одному сообщению для каждого неудачного теста

CK_ENV - Получает режим печати из переменной окружения CK_VERBOSITY, которая может иметь значения "silent", "minimal", "normal", "verbose". Если переменная не найдена или значение не распознано, режим печати устанавливается в CK_NORMAL

CK_SUBUNIT - Выводит ход выполнения через протокол subunit testrunner. https://launchpad.net/subunit/

>>> Написать Makefile

В мейкфайле я прикрепил пояснения в комментариях.

------

Если будут вопросы - обращайтесь :)
@superboy