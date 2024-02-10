#include "AutoTest.h"
#include "MyString.h"
#include <stdexcept>
#include <utility>
#include <cstring>

#define CHECK_RAW_STRING_EQUAL(string, data, message)													\
		CHECK_EQUAL(strcmp((string).c_str(), data), 0, message);

#define CHECK_RAW_STRING_NOT_EQUAL(string, data, message)												\
		CHECK_NOT_EQUAL(strcmp((string).c_str(), data), 0, message);

#define CHECK_STRING_EQUAL(string1, string2, message)													\
	CHECK_RAW_STRING_EQUAL(string1, (string2).c_str(), message)

#define CHECK_STRING_NOT_EQUAL(string1, string2, message)												\
	CHECK_RAW_STRING_NOT_EQUAL(string1, (string2).c_str(), message)
	

int main(int argc, const char **argv)
{
	START_TEST(argc, argv);

		START_EXERCISE(MyStringClass);

			// Constructor por defecto
			{
				const MyString empty;
				CHECK_RAW_STRING_EQUAL(empty, "", "El constructor por defecto es incorrecto");
			}

			// Constructor tamaño N dado
			{
				const size_t size = 10;
				const MyString nsized{size};
				CHECK_EQUAL(nsized.length(), size, "El constructor de tamaño n dado es incorrecto");
			}

			// Constructor tamaño N dado con mismo carácter
			{
				const size_t size = 10;
				const MyString nsizedRepeatChar{size, '*'};
				CHECK_RAW_STRING_EQUAL(nsizedRepeatChar, "**********", "El constructor de tamaño n dado con el mismo carácter es incorrecto");
			}

			// Constructor a partir de const char*
			{
				const char* helloworld = "hello world";
				const MyString helloworldStr{helloworld};
				CHECK_RAW_STRING_EQUAL(helloworldStr, helloworld, "El constructor a partir de un const char* no es correcto");
			}

			// Constructor de copia
			{
				const MyString helloworld{"hello world"};
				MyString helloworldCopy(helloworld);
				CHECK_STRING_EQUAL(helloworld, helloworldCopy, "El constructor de copia no es correcto");
			}

			// Método c_str()
			{
				const MyString helloworld{"hello world"};
				const char* cMyStringContent = helloworld.c_str();
				CHECK_RAW_STRING_EQUAL(helloworld, cMyStringContent, "El método c_str() no es correcto");
			}

			// Método length
			{
				const MyString helloworld{"hello world"};
				CHECK_EQUAL(helloworld.length(), strlen(helloworld.c_str()), "El método length() no es correcto");
				const MyString empty{""};
				CHECK_EQUAL(empty.length(), 0, "La implementación del método length() no es correcta para cadenas vacías.")
			}

			// Asignar const char*
			{
				const char* helloworld = "hello world";
				const MyString helloworldStr = helloworld;
				CHECK_RAW_STRING_EQUAL(helloworldStr, helloworld, "El operador de asignación a partir de un const char* no es correcto");
			}

			// Asignar a partir de otro MyString
			{
				const MyString helloworldStr1 = "hello world";
				const MyString helloworldStr2 = helloworldStr1;
				CHECK_STRING_EQUAL(helloworldStr1, helloworldStr2, "El operador de asignación a partir de un MyString no es correcto");
			}

			// operadores relacionales
			{
				START_COMPOSED_CHECK();
					const char* helloworld = "hello world";
					const MyString str1("hello world");
					const MyString str2("byebyeworld");
					const MyString str3("hello world");

					CHECK_EQUAL(str1 == str3, true, "La implementación del operador== entre MyStrings no es correcta");
					CHECK_EQUAL(str1 == helloworld, true, "La implementación del operador== entre un MyString y un const char* no es correcta");
					CHECK_EQUAL(str1 != str3, false, "La implementación del operador!= entre MyStrings no es correcta");
					CHECK_EQUAL(str1 != helloworld, false, "La implementación del operador!= entre un MyString y un const char* no es correcta");

					CHECK_EQUAL(str1 > str3, false, "La implementación del operador> entre dos MyString no es correcta");
					CHECK_EQUAL(str1 > str2, true, "La implementación del operador> entre dos MyString no es correcta");
					CHECK_EQUAL(str1 > helloworld, false, "La implementación del operador> entre un MyString y un const char* no es correcta");

					CHECK_EQUAL(str1 >= str3, true, "La implementación del operador>= entre dos MyString no es correcta");
					CHECK_EQUAL(str1 >= str2, true, "La implementación del operador>= entre dos MyString no es correcta");
					CHECK_EQUAL(str1 >= helloworld, true, "La implementación del operador>= entre un MyString y un const char* no es correcta");
					
					CHECK_EQUAL(str1 < str3, false, "La implementación del operador< entre dos MyString no es correcta");
					CHECK_EQUAL(str1 < str2, false, "La implementación del operador< entre dos MyString no es correcta");
					CHECK_EQUAL(str1 < helloworld, false, "La implementación del operador< entre un MyString y un const char* no es correcta");

					CHECK_EQUAL(str1 <= str3, true, "La implementación del operador<= entre dos MyString no es correcta");
					CHECK_EQUAL(str1 <= str2, false, "La implementación del operador<= entre dos MyString no es correcta");
					CHECK_EQUAL(str1 <= helloworld, true, "La implementación del operador<= entre un MyString y un const char* no es correcta");
				END_COMPOSED_CHECK();
			}

			// operador +
			{
				START_COMPOSED_CHECK();
					const MyString str1("helloworld");
					const MyString str2("byebyeworld");
					const MyString empty("");

					CHECK_RAW_STRING_EQUAL(str1 + str2, "helloworldbyebyeworld", "La implementación del operador+ entre MyStrings no es correcta");
					CHECK_RAW_STRING_EQUAL(str1 + empty, "helloworld", "La implementación del operador+ entre MyStrings no es correcta");
					CHECK_RAW_STRING_EQUAL(str1 + "byebyeworld", "helloworldbyebyeworld", "La implementación del operador+ entre un MyString y un const char* no es correcta");
					CHECK_RAW_STRING_EQUAL(str1 + "", "helloworld", "La implementación del operador+ entre un MyString y un const char* no es correcta");

					MyString str3 = str1;
					str3 += str2;
					CHECK_RAW_STRING_EQUAL(str3, "helloworldbyebyeworld", "La implementación del operador+= entre dos MyStrings no es correcta");

					MyString str4 = str1;
					str4 += "byebyeworld";
					CHECK_RAW_STRING_EQUAL(str4, "helloworldbyebyeworld", "La implementación del operador+= entre un MyString y un const char* no es correcta");
				END_COMPOSED_CHECK();
			}

			// operador []
			{
				START_COMPOSED_CHECK();
					const MyString helloworldStr1 = "hello world";
					const char& c1 = helloworldStr1[0];
					CHECK_EQUAL(c1, 'h', "La implementación del operador[] en su versión constante no es correcta");

					MyString helloworldStr2 = "hello world";
					char& c2 = helloworldStr2[0];
					CHECK_EQUAL(c2, 'h', "La implementación del operador[] en su versión no constante no es correcta");
				END_COMPOSED_CHECK();
			}

			// Método at()
			{
				START_COMPOSED_CHECK();
					const MyString helloworldStr1 = "hello world";
					const char& c1 = helloworldStr1.at(0);
					CHECK_EQUAL(c1, 'h', "La implementación del método at() en su versión constante no es correcta");

					MyString helloworldStr2 = "hello world";
					char& c2 = helloworldStr2.at(0);
					CHECK_EQUAL(c2, 'h', "La implementación del método at() en su versión no constante no es correcta");

					try // acceso con at() constante fuera de los límites del MyString
					{
						const char& c = helloworldStr1.at(1000);
						CHECK_EQUAL(true, false, "Se esperaba una excepción cuando se accede(const) fuera de los límites del MyString");
					}
					catch(const std::out_of_range& oor)
					{
						const char* reason = oor.what();
						UNUSED(reason);
						CHECK_NOT_EQUAL(strlen(reason), 0, "Se envía una excepción cuando se accede(const) fuera de los límites del MyString pero el mensaje está vacío");
					}
					try // acceso con at() no constante fuera de los límites del MyString
					{
						char& c = helloworldStr2.at(1000);
						CHECK_EQUAL(true, false, "Se esperaba una excepción cuando se accede(no const) fuera de los límites del MyString");
					}
					catch(const std::out_of_range& oor)
					{
						const char* reason = oor.what();
						UNUSED(reason);
						CHECK_NOT_EQUAL(strlen(reason), 0, "Se envía una excepción cuando se accede(no const) fuera de los límites del MyString pero el mensaje está vacío");
					}
				END_COMPOSED_CHECK();
			}

			// Método substr
			{
				START_COMPOSED_CHECK();
					const MyString helloworldStr1 = "hello world";
					const MyString ld1 = helloworldStr1.substr(9, 2);
					CHECK_RAW_STRING_EQUAL(ld1, "ld", "La implementación del método substr() para un MyString constante no es correcta");
					MyString helloworldStr = "hello world";
					const MyString ld2 = helloworldStr.substr(9, 2);
					CHECK_RAW_STRING_EQUAL(ld2, "ld", "La implementación del método substr() para un MyString no constante no es correcta");
				END_COMPOSED_CHECK();
			}

			// operador=
			{
				START_COMPOSED_CHECK();
					const char* helloworld = "const char* hello world";
					MyString helloworldStr = "hello world";
					MyString byebyeworldStr = "byebyeworld";

					helloworldStr = helloworld;
					CHECK_RAW_STRING_EQUAL(helloworldStr, helloworld, "La implementación del operador= para un MyString y un const char* no es correcta");
					helloworldStr = byebyeworldStr;
					CHECK_RAW_STRING_EQUAL(helloworldStr, "byebyeworld", "La implementación del operador= entre dos MyStrings no es correcta");

				END_COMPOSED_CHECK();
			}

			// operador= &&
			{
				START_COMPOSED_CHECK();
					MyString helloworldStr = "hello world";
					MyString byebyeworldStr = "byebyeworld";

					helloworldStr = std::move(byebyeworldStr);
					CHECK_EQUAL(byebyeworldStr.c_str(), nullptr, "La implementación del operador=&& entre dos MyStrings no es correcta. El contenido del movido no es nullptr.");
					CHECK_EQUAL(byebyeworldStr.length(), 0, "La implementación del operador=&& entre dos MyStrings no es correcta. La longitud del movido no es cero.");
					CHECK_EQUAL(helloworldStr.length(), 11, "La implementación del operador=&& entre dos MyStrings no es correcta. La longitud del destino no es correcta.");
					CHECK_RAW_STRING_EQUAL(helloworldStr, "byebyeworld", "La implementación del operador=&& entre dos MyStrings no es correcta. El contenido del destino no es el correcto.");

				END_COMPOSED_CHECK();
			}

			// constructor &&
			{
				START_COMPOSED_CHECK();
					MyString helloworldStr{"hello world"};
					MyString byebyeworldStr(std::move(helloworldStr));

					CHECK_EQUAL(helloworldStr.c_str(), nullptr, "La implementación del constructor&& entre dos MyStrings no es correcta. El contenido del movido no es nullptr.");
					CHECK_EQUAL(helloworldStr.length(), 0, "La implementación del constructor=&& entre dos MyStrings no es correcta. La longitud del movido no es cero.");

					CHECK_RAW_STRING_EQUAL(byebyeworldStr, "hello world", "La implementación del operador=&& entre dos MyStrings no es correcta. El contenido del destino no es el correcto.");
					CHECK_EQUAL(byebyeworldStr.length(), 11, "La implementación del operador=&& entre dos MyStrings no es correcta. La longitud del destino no es correcta.");
				END_COMPOSED_CHECK();
			}


		END_EXERCISE();

	END_TEST();

	return 0;
}