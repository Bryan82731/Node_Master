/*********************************************
2017_10_07
��@���ܼƩ�b�o��
*********************************************/


int check_same = 0;
bool MAC_flag = 0;      //0�N���٨S����Slave��MAC 1�h�Ϥ�
bool flash_flag = 0;       //0�N���٨S����Slave��lat lon 1�h�Ϥ�
int MAC_ad[6];          //�x�sSlave��MAC


/*********************************************************************
Buffer�����ܼ�
*/
#define device_number   36//����buffer�ƥ�
#define CLK                   48/2//�X�Ӵ`����M����T  48�ӳ���5��


int  buffer_now_count_to = 0;//�{�b����ĴX��Buffer

typedef struct 
{
  char data[31];
  bool uart_to_slave; // 1�N��ǰe����  0 �h�_
  bool protection;      //��ƫO�@ 1�i�R 0���i
  bool have_data;       //1 = ������� 0�h�L
  int count;                 //��ƫO�@�ɶ� �g�LCLK��R��
}devicedata;

devicedata device[36];

  

int flash[20]={0};
/*********************************************************************
 * �g�n�׬���
 */
//�ۤv����
uint8 MyHigh;                   //�ۨ�����
uint8 MyLight_lat_H;        //�ۨ��n��H��
uint8 MyLight_lat_L;        //�ۨ��n��L��   
uint8 MyLight_lon_H;      //�ۨ��g��H��
uint8 MyLight_lon_L;      //�ۨ��g��L��
int MyLight_lat;              //�ۨ��n��      
int MyLight_lon;             //�ۨ��g��
uint8 location_code;        //Router�ϽX
//���I����
uint8 Router_lat_H;     //���I���n��H��
uint8 Router_lat_L;     //���I���n��L��
uint8 Router_lon_H;    //���I���g��H��
uint8 Router_lon_L;    //���I���g��L��
int Router_lat;         //���I�n��
int Router_lon;        //���I�g��

/*********************************************************************
���y���ܼ�
*/
bool Match_distance_answer;     //���Z�������G0�N��  1�N���
int same_count; //����buffer����m



#include <scif.h>
#include <BIOS.h>
Task_Struct my_UART_Task;
Char my_UART_TaskStack[512];
static Semaphore_Struct semScTaskAlert;
int rxbuf[100];
static PIN_Handle hSbpPins;
bool start_flag = 0;
char newValue[20];
char change_to_char[63];



extern void next_buffer(int *count);
extern bool Match_distance(char *input_data,int my_lon,int my_lat,int router_lon,int router_lat);
