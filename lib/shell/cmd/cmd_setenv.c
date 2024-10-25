#include <stdio.h>
#include <string.h>
#include "command.h"


typedef struct {
    uint8_t para1;
    uint8_t para2;
    uint8_t para3;
} sparament;

// ����������Ļ�������
sparament environment_variable={
  .para1 =1,
	.para2 =2,
	.para3 =3,
};


static int setenv(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: setenv <parameter> <value>\r\n");
        return 1;  // ���ش�����
    }

    // ��ȡ���������Ĳ�������ֵ
    char *parameter_name = argv[1];
    uint8_t value;

    // �������в����л�ȡֵ
    if (sscanf(argv[2], "%hhu", &value) != 1) {
        fprintf(stderr, "Invalid value\r\n");
        return 1;
    }

    // ���ݲ�����������Ӧ�Ļ�������
    if (strcmp(parameter_name, "para1") == 0) {
        environment_variable.para1 = value;
    } else if (strcmp(parameter_name, "para2") == 0) {
        environment_variable.para2 = value;
    } else if (strcmp(parameter_name, "para3") == 0) {
        environment_variable.para3 = value;
    } else {
        fprintf(stderr, "Invalid parameter name\r\n");
        return 1;
    }

    // ���������ִ���������û��������Ĳ��������籣�浽�ļ����������ط�

    printf("Environment variable set: %s=%u\r\n", parameter_name, value);

    return 0;  // ���سɹ���
}

struct command sevent_cmd = {
    "setenv",
    "Setting environment variables\r\n",
    "Usage: sevent <parameter> <value>\r\n",
    setenv,
};




//��ӡ���е�ǰ����������ֵ
static int printenv(int argc, char **argv) {

     // ��ӡ��������
    printf("para1=%u\r\n", environment_variable.para1);
    printf("para2=%u\r\n", environment_variable.para2);
    printf("para3=%u\r\n", environment_variable.para3);
    return 0;  // ���سɹ���
}

struct command printeven_cmd = {
    "env",
    "print all environment variables\r\n",
    "Usage: printenv\r\n",
    printenv,
};
