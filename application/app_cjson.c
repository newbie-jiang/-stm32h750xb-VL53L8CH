#include "app_config.h"



/*use cmsis cjson pack v1.7.7*/

//#include "cJSON.h"  // cJSON���ͷ�ļ�
#include "bsp_usart.h"  // UART������ͷ�ļ�������������������Ӳ���Ϳ�����������

//// ��������
//void sendJsonDataViaUART(cJSON *jsonObject);

//int test_cjson_send() {
//    // ����һ���򵥵�JSON����
//    cJSON *jsonObject = cJSON_CreateObject();
//  

//    // ��ӻ�����Ϣ
//    cJSON_AddStringToObject(jsonObject, "name", "John Doe");
//    cJSON_AddNumberToObject(jsonObject, "age", 30);
//    cJSON_AddStringToObject(jsonObject, "city", "New York");

//    // ��Ӳ���ֵ
//    cJSON_AddFalseToObject(jsonObject, "isStudent");

//    // �������
//    cJSON *gradesArray = cJSON_CreateArray();
//    cJSON_AddItemToArray(gradesArray, cJSON_CreateNumber(90));
//    cJSON_AddItemToArray(gradesArray, cJSON_CreateNumber(85));
//    cJSON_AddItemToArray(gradesArray, cJSON_CreateNumber(92));
//    cJSON_AddItemToObject(jsonObject, "grades", gradesArray);

//    // ���Ƕ�׵Ķ���
//    cJSON *addressObject = cJSON_CreateObject();
//    cJSON_AddStringToObject(addressObject, "street", "123 Main St");
//    cJSON_AddStringToObject(addressObject, "city", "Anytown");
//    cJSON_AddStringToObject(addressObject, "zipCode", "12345");
//    cJSON_AddItemToObject(jsonObject, "address", addressObject);
//   
//    // ���÷��ͺ���
//    sendJsonDataViaUART(jsonObject);

//    // �ͷ�JSON����
//    cJSON_Delete(jsonObject);

//    return 0;
//}

//// ��������
//void sendJsonDataViaUART(cJSON *jsonObject) {
//    // ��JSON����ת��Ϊ�ַ���
//    char *jsonString = cJSON_Print(jsonObject);

//    // ����uart_send����������UART���ͺ���������ʵ�ָ�������Ӳ������������
//    putstr(jsonString);

//    // �ͷ��ڴ�
//    cJSON_free(jsonString);
//}





//// ��������
//cJSON* parseReceivedJsonData(const char *jsonString);


//// ģ����� UART ���ݵĺ���
//const char *receiveJsonDataFromUART() {
//    static char receivedData[256];  // ������ջ�������СΪ 256 �ֽ�
//    printf("Enter JSON data: ");
//    scanf("%255s", receivedData);  // ���������ַ������ȣ���ֹ���������
//    return receivedData;
//}

//int test_cjson_receive() {
//    // ���� receiveJsonDataFromUART ����������UART���պ��������ؽ��յ���JSON�ַ���
//    const char *receivedJsonString = receiveJsonDataFromUART();

//    // �������յ���JSON�ַ���
//    cJSON *receivedJsonObject = parseReceivedJsonData(receivedJsonString);

//    // ����������JSON���������ȡ���е�����
//    if (receivedJsonObject != NULL) {
//        cJSON *nameItem = cJSON_GetObjectItem(receivedJsonObject, "name");
//        if (nameItem != NULL && nameItem->type == cJSON_String) {
//            printf("Received Name: %s\n", nameItem->valuestring);
//        }

//        // �ͷŽ������JSON����
//        cJSON_Delete(receivedJsonObject);
//    }

//    return 0;
//}

//// ��������
//cJSON* parseReceivedJsonData(const char *jsonString) {
//    // ʹ�� cJSON_Parse ��������JSON�ַ���
//    cJSON *jsonObject = cJSON_Parse(jsonString);

//    // �������Ƿ�ɹ�
//    if (jsonObject == NULL) {
//        const char *errorPtr = cJSON_GetErrorPtr();
//        if (errorPtr != NULL) {
//            printf("JSON Parsing Error: %s\n", errorPtr);
//        }
//    }

//    return jsonObject;
//}



