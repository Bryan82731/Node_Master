/*********************************************
2017_10_07
把一些變數放在這裡
*********************************************/


int check_same = 0;
bool MAC_flag = 0;      //0代表還沒收到Slave的MAC 1則反之
bool flash_flag = 0;       //0代表還沒收到Slave的lat lon 1則反之
int MAC_ad[6];          //儲存Slave之MAC


/*********************************************************************
Buffer相關變數
*/
#define device_number   36//內部buffer數目
#define CLK                   48/2//幾個循環後清除資訊  48個單位約5秒


int  buffer_now_count_to = 0;//現在指到第幾格Buffer

typedef struct 
{
  char data[31];
  bool uart_to_slave; // 1代表傳送完畢  0 則否
  bool protection;      //資料保護 1可刪 0不可
  bool have_data;       //1 = 內有資料 0則無
  int count;                 //資料保護時間 經過CLK後刪除
}devicedata;

devicedata device[36];

  

int flash[20]={0};
/*********************************************************************
 * 經緯度相關
 */
//自己有關
uint8 MyHigh;                   //自身高度
uint8 MyLight_lat_H;        //自身緯度H位
uint8 MyLight_lat_L;        //自身緯度L位   
uint8 MyLight_lon_H;      //自身經度H位
uint8 MyLight_lon_L;      //自身經度L位
int MyLight_lat;              //自身緯度      
int MyLight_lon;             //自身經度
uint8 location_code;        //Router區碼
//終點有關
uint8 Router_lat_H;     //終點之緯度H位
uint8 Router_lat_L;     //終點之緯度L位
uint8 Router_lon_H;    //終點之經度H位
uint8 Router_lon_L;    //終點之經度L位
int Router_lat;         //終點緯度
int Router_lon;        //終點經度

/*********************************************************************
掃描時變數
*/
bool Match_distance_answer;     //比對距離的結果0代表遠  1代表近
int same_count; //重複buffer之位置



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
