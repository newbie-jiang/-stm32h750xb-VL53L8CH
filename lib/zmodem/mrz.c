#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zmodem.h"
#include "command.h"

#include "boot.h"
#include "config.h"
 size_t rz_bytes;
	
	
int rz(int argc, char *argv[])
{
	
//	 if (argc != 2) {
//        fprintf(stderr, "Usage: rz <address>\r\n");
//        return 1;  // ���ش�����
//    }
	
//  int c;
  bool bps_flag = false;
  uint64_t bps = 0u;

       rz_bytes = zmodem_receive(NULL, /* use current directory */
				NULL, /* receive everything */
				NULL,
				NULL,
				bps_flag ? bps : 0,
				RZSZ_FLAGS_NONE);
	
	  
	
//  fprintf(stderr, "Received %zu bytes.\r\n", bytes);
  return 0;
}

struct command rz_cmd = {
	"rz",
		
	"receive file through z modem\r\n",
	
	"Usage: \r\n"
	"       rz <mem address>\r\n",

	rz,
};




