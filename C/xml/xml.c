#include <stdio.h>
#include <jansson.h>
#include <string.h>

void test(int a, int b)
{
    printf("%d %d %d\n", a, b, a+b);
}

int main(int argc, char **argv)
{
    json_error_t e;
    json_t *map = json_load_file("1.json", 0, &e);

    printf("%d %s:%d:%d %s\n", json_array_size(map), e.source, e.line, e.column, e.text);
    for (int i = 0; i < json_array_size(map); i++)
    {
	json_t *object, *args, *typeobj;
	char *type;
	object = json_array_get(map, i);

	typeobj = json_object_get(object, "type");

	type = (char*)json_string_value(typeobj);

	printf("%s\n", type);
	if (strcmp(type, "player\n"))
	{
	    printf("it's a player!\n");
	    json_t *args, *xobj, *yobj;
	    int x, y;


	    args = json_object_get(object, "args");
	    xobj = json_array_get(args, 0);
	    yobj = json_array_get(args, 1);

	    test(json_integer_value(xobj), json_integer_value(yobj));
	}

	json_decref(map);
    }
}
