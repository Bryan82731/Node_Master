////////////////////////////////////////////////要加這些,不然某些int bool不能用
#include <stdbool.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Queue.h>

#ifdef USE_ICALL
#include <ICall.h>
#else
#include <stdlib.h>
#endif

#include "bcomdef.h"
#include "util.h"
////////////////////////////////////////////////

#include "math.h"


/*********************************************************************
 * @fn      next_buffer
 *
 * @brief   把buffer存檔指標往上加,超過歸零
 *
 * @return  none
 */
void next_buffer(int *count)
{
  *count  = *count + 1;
  
  if(*count > 36)
    *count = 0;
}


/*********************************************************************
 * @fn      Match_distance
 *
 * @brief   比對此封包之位置和終點之差,和我經緯度和終點之差
 *
 * @return  1代表我比較近   0代表我不用傳(刪除或忽略)
 */
bool Match_distance(char *input_data,int my_lon,int my_lat,int router_lon,int router_lat)
{
  int data_lon,data_lat;
  float router_lon_to_data_lon;
  float router_lat_to_data_lat;
  float RouterDis_to_data;
  
  float router_lon_to_my_lon;
  float router_lat_to_my_lat;
  float RouterDis_to_me; 
  
  //先把16進制會成十進制
  data_lon = ((*(input_data+25) & 0xF0)>>4)*1000 + (*(input_data+25) & 0x0F)*100 + ((*(input_data+26) & 0xF0)>>4)*10 + (*(input_data+26) & 0x0F);
  data_lat = ((*(input_data+27) & 0xF0)>>4)*1000 + (*(input_data+27) & 0x0F)*100 + ((*(input_data+28) & 0xF0)>>4)*10 + (*(input_data+28) & 0x0F);
  
  //取此資料與終點多遠
  router_lon_to_data_lon = pow(router_lon - data_lon,2);
  router_lat_to_data_lat = pow(router_lat - data_lat,2);
  RouterDis_to_data = sqrt(router_lon_to_data_lon + router_lat_to_data_lat);
  
  //再算我距離至終點多遠
  router_lon_to_my_lon = pow(router_lon - my_lon,2);
  router_lat_to_my_lat = pow(router_lat - my_lat,2);
  RouterDis_to_me = sqrt(router_lon_to_my_lon + router_lat_to_my_lat);

  //比對距離
  if(RouterDis_to_data >= RouterDis_to_me)
    return 1;
  else
    return 0;
  
  
}
