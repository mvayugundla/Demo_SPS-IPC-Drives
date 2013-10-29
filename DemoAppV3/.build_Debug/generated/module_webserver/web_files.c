#include "simplefs.h"

#include "stdlib.h"

#include "web_server.h"

#ifdef __web_server_conf_h_exists__
#include "web_server_conf.h"
#endif

char _data_web_default_favicon_dot_gif[] = {72,84,84,80,47,49,46,48,32,50,48,48,32,79,75,13,10,83,101,114,118,101,114,58,32,88,77,79,83,13,10,67,111,110,116,101,110,116,45,116,121,112,101,58,32,105,109,97,103,101,47,103,105,102,13,10,13,10,71,73,70,56,57,97,16,0,16,0,230,0,0,38,80,158,38,51,104,64,64,64,14,30,59,48,48,48,89,157,42,32,32,32,28,28,28,13,28,56,32,55,15,6,11,3,114,114,112,69,7,25,20,20,19,222,222,221,29,46,13,41,57,115,34,43,87,81,8,29,112,112,112,42,42,42,169,169,168,55,55,55,168,20,66,166,16,59,13,25,49,228,228,227,199,199,198,14,11,23,124,75,48,71,124,33,86,126,57,14,23,6,7,14,28,50,50,50,5,8,2,92,105,39,33,70,138,66,6,24,7,14,29,30,33,13,60,60,60,188,23,76,17,17,36,12,24,47,105,70,41,228,22,81,143,143,142,199,19,71,209,209,208,113,113,111,223,223,223,83,145,39,191,191,190,34,70,139,22,37,10,242,242,241,52,52,52,36,36,35,61,6,22,153,153,152,43,61,123,94,93,39,214,21,76,81,71,33,185,18,66,102,178,48,64,111,30,191,191,191,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,33,249,4,0,0,0,0,0,44,0,0,0,0,16,0,16,0,0,7,139,128,70,130,131,70,39,25,43,38,12,40,9,55,132,131,8,54,16,23,48,45,5,30,35,142,70,3,0,61,42,46,29,66,52,10,153,155,1,65,63,64,66,67,163,142,165,167,169,67,153,154,0,166,168,170,178,8,180,175,183,153,33,37,181,176,178,70,44,17,187,177,194,28,24,182,199,194,18,65,62,183,19,69,211,212,26,27,11,59,36,188,68,51,68,222,222,60,34,7,15,5,204,4,223,223,69,2,70,9,31,50,47,21,53,49,14,56,212,211,6,70,32,13,7,58,20,4,57,22,82,8,24,40,0,159,176,131,129,0,0,59};

fs_file_t _web_default_favicon_dot_gif = {NULL,1,616,(simplefs_addr_t) &_data_web_default_favicon_dot_gif[0],{100,101,102,97,117,108,116,95,102,97,118,105,99,111,110,46,103,105,102,0}};

char _data_web_index_dot_html[] = {72,84,84,80,47,49,46,48,32,50,48,48,32,79,75,13,10,83,101,114,118,101,114,58,32,88,77,79,83,13,10,67,111,110,116,101,110,116,45,116,121,112,101,58,32,116,101,120,116,47,104,116,109,108,13,10,13,10,60,104,116,109,108,62,13,10,60,104,101,97,100,62,13,10,60,116,105,116,108,101,62,88,77,79,83,32,71,80,73,79,32,87,101,98,115,101,114,118,101,114,60,47,116,105,116,108,101,62,13,10,60,47,104,101,97,100,62,13,10,60,98,111,100,121,62,13,10,60,104,49,62,120,83,79,70,84,105,112,32,71,80,73,79,32,97,110,100,32,87,105,45,70,105,32,68,101,109,111,32,65,112,112,108,105,99,97,116,105,111,110,60,47,104,49,62,13,10,60,112,62,84,104,105,115,32,105,115,32,97,110,32,101,120,97,109,112,108,101,32,97,112,112,108,105,99,97,116,105,111,110,32,116,111,32,115,104,111,119,99,97,115,101,32,71,80,73,79,32,102,101,97,116,117,114,101,115,32,117,115,105,110,103,32,97,32,119,101,98,32,112,97,103,101,60,47,112,62,13,10,60,112,62,255,8,60,47,112,62,13,10,60,102,111,114,109,32,110,97,109,101,61,34,102,111,114,109,34,32,97,99,116,105,111,110,32,61,32,34,34,32,109,101,116,104,111,100,61,34,112,111,115,116,34,62,13,10,60,112,62,77,111,100,105,102,121,32,76,69,68,115,32,83,116,97,116,101,32,58,60,47,112,62,13,10,60,116,97,98,108,101,32,98,111,114,100,101,114,61,39,49,39,62,13,10,60,116,114,62,13,10,60,116,100,32,119,105,100,116,104,61,39,49,53,48,39,62,76,69,68,32,48,60,47,116,100,62,13,10,60,116,100,32,119,105,100,116,104,61,39,55,48,39,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,48,39,32,105,100,61,39,108,48,39,32,118,97,108,117,101,61,39,48,39,32,255,0,62,79,102,102,60,47,116,100,62,13,10,60,116,100,32,119,105,100,116,104,61,39,55,48,39,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,48,39,32,105,100,61,39,108,48,39,32,118,97,108,117,101,61,39,49,39,32,255,1,62,79,110,60,47,116,100,62,13,10,60,47,116,114,62,13,10,60,116,114,62,13,10,60,116,100,32,119,105,100,116,104,61,39,49,53,48,39,62,76,69,68,32,49,60,47,116,100,62,13,10,60,116,100,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,49,39,32,105,100,61,39,108,49,39,32,118,97,108,117,101,61,39,48,39,32,255,2,62,79,102,102,60,47,116,100,62,13,10,60,116,100,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,49,39,32,105,100,61,39,108,49,39,32,118,97,108,117,101,61,39,49,39,32,255,3,62,79,110,60,47,116,100,62,13,10,60,47,116,114,62,13,10,60,116,114,62,13,10,60,116,100,32,119,105,100,116,104,61,39,49,53,48,39,62,76,69,68,32,50,60,47,116,100,62,13,10,60,116,100,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,50,39,32,105,100,61,39,108,50,39,32,118,97,108,117,101,61,39,48,39,32,255,4,62,79,102,102,60,47,116,100,62,13,10,60,116,100,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,50,39,32,105,100,61,39,108,50,39,32,118,97,108,117,101,61,39,49,39,32,255,5,62,79,110,60,47,116,100,62,13,10,60,47,116,114,62,13,10,60,116,114,62,13,10,60,116,100,32,119,105,100,116,104,61,39,49,53,48,39,62,76,69,68,32,51,60,47,116,100,62,13,10,60,116,100,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,51,39,32,105,100,61,39,108,51,39,32,118,97,108,117,101,61,39,48,39,32,255,6,62,79,102,102,60,47,116,100,62,13,10,60,116,100,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,51,39,32,105,100,61,39,108,51,39,32,118,97,108,117,101,61,39,49,39,32,255,7,62,79,110,60,47,116,100,62,13,10,60,47,116,114,62,13,10,60,47,116,97,98,108,101,62,13,10,60,112,62,255,9,60,47,112,62,13,10,60,112,62,255,10,60,47,112,62,13,10,60,105,110,112,117,116,32,116,121,112,101,61,34,115,117,98,109,105,116,34,32,86,97,108,117,101,61,34,83,117,98,109,105,116,34,47,62,13,10,60,47,102,111,114,109,62,13,10,60,47,98,111,100,121,62,13,10,60,47,104,116,109,108,62,13,10};

fs_file_t _web_index_dot_html = {&_web_default_favicon_dot_gif,0,1164,(simplefs_addr_t) &_data_web_index_dot_html[0],{105,110,100,101,120,46,104,116,109,108,0}};

char _data_web_interface_dot_html[] = {72,84,84,80,47,49,46,48,32,50,48,48,32,79,75,13,10,83,101,114,118,101,114,58,32,88,77,79,83,13,10,67,111,110,116,101,110,116,45,116,121,112,101,58,32,116,101,120,116,47,104,116,109,108,13,10,13,10,60,104,116,109,108,62,13,10,60,104,101,97,100,62,13,10,60,116,105,116,108,101,62,73,78,68,85,83,84,82,89,32,52,46,48,32,68,69,77,79,60,47,116,105,116,108,101,62,13,10,60,115,116,121,108,101,62,13,10,104,116,109,108,44,98,111,100,121,32,123,13,10,104,101,105,103,104,116,58,32,49,48,48,37,59,13,10,119,105,100,116,104,58,32,49,48,48,37,59,13,10,109,97,114,103,105,110,58,32,51,48,32,48,59,13,10,125,13,10,102,111,114,109,123,13,10,104,101,105,103,104,116,58,32,49,48,48,37,59,13,10,119,105,100,116,104,58,32,49,48,48,37,59,13,10,109,97,114,103,105,110,58,32,48,59,13,10,125,13,10,60,47,115,116,121,108,101,62,13,10,60,47,104,101,97,100,62,13,10,60,98,111,100,121,32,98,103,99,111,108,111,114,32,61,32,34,35,56,52,56,52,56,52,34,62,13,10,60,99,101,110,116,101,114,62,13,10,60,104,49,62,87,69,76,67,79,77,69,32,84,79,32,83,89,78,65,80,84,73,67,79,78,32,67,79,67,75,84,65,73,76,32,66,65,82,33,60,47,104,49,62,13,10,60,105,109,103,32,115,114,99,61,34,100,101,102,97,117,108,116,95,102,97,118,105,99,111,110,46,103,105,102,34,32,97,108,116,61,34,83,121,110,97,112,116,105,99,111,110,32,108,111,103,111,34,32,119,105,100,116,104,61,34,54,48,34,32,104,101,105,103,104,116,61,34,54,48,34,62,13,10,60,98,114,62,60,98,114,62,60,98,114,62,13,10,60,102,111,114,109,32,110,97,109,101,61,34,102,111,114,109,34,32,97,99,116,105,111,110,32,61,32,34,34,32,109,101,116,104,111,100,61,34,112,111,115,116,34,62,13,10,60,104,50,62,80,105,99,107,32,97,32,99,111,99,107,116,97,105,108,33,60,47,104,50,62,13,10,60,116,97,98,108,101,32,98,111,114,100,101,114,61,39,48,39,32,99,101,108,108,115,112,97,99,105,110,103,61,34,51,48,34,62,13,10,60,116,114,62,13,10,60,116,100,32,119,105,100,116,104,61,39,49,53,48,39,62,82,101,99,105,112,101,49,60,47,116,100,62,13,10,60,116,100,32,119,105,100,116,104,61,39,55,48,39,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,48,39,32,105,100,61,39,108,48,39,32,118,97,108,117,101,61,39,48,39,32,255,0,62,79,102,102,60,47,116,100,62,13,10,60,116,100,32,119,105,100,116,104,61,39,55,48,39,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,48,39,32,105,100,61,39,108,48,39,32,118,97,108,117,101,61,39,49,39,32,255,1,62,79,110,60,47,116,100,62,13,10,60,47,116,114,62,13,10,60,116,114,62,13,10,60,116,100,32,119,105,100,116,104,61,39,49,53,48,39,62,82,101,99,105,112,101,50,60,47,116,100,62,13,10,60,116,100,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,49,39,32,105,100,61,39,108,49,39,32,118,97,108,117,101,61,39,48,39,32,255,2,62,79,102,102,60,47,116,100,62,13,10,60,116,100,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,49,39,32,105,100,61,39,108,49,39,32,118,97,108,117,101,61,39,49,39,32,255,3,62,79,110,60,47,116,100,62,13,10,60,47,116,114,62,13,10,60,116,114,62,13,10,60,116,100,32,119,105,100,116,104,61,39,49,53,48,39,62,82,101,99,105,112,101,51,60,47,116,100,62,13,10,60,116,100,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,50,39,32,105,100,61,39,108,50,39,32,118,97,108,117,101,61,39,48,39,32,255,4,62,79,102,102,60,47,116,100,62,13,10,60,116,100,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,50,39,32,105,100,61,39,108,50,39,32,118,97,108,117,101,61,39,49,39,32,255,5,62,79,110,60,47,116,100,62,13,10,60,47,116,114,62,13,10,60,116,114,62,13,10,60,116,100,32,119,105,100,116,104,61,39,49,53,48,39,62,82,101,99,105,112,101,52,60,47,116,100,62,13,10,60,116,100,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,51,39,32,105,100,61,39,108,51,39,32,118,97,108,117,101,61,39,48,39,32,255,6,62,79,102,102,60,47,116,100,62,13,10,60,116,100,62,60,105,110,112,117,116,32,116,121,112,101,61,34,114,97,100,105,111,34,32,110,97,109,101,61,39,108,51,39,32,105,100,61,39,108,51,39,32,118,97,108,117,101,61,39,49,39,32,255,7,62,79,110,60,47,116,100,62,13,10,60,47,116,114,62,13,10,60,47,116,97,98,108,101,62,13,10,60,98,114,62,13,10,60,98,114,62,13,10,60,105,110,112,117,116,32,116,121,112,101,61,34,115,117,98,109,105,116,34,32,86,97,108,117,101,61,34,83,117,98,109,105,116,34,47,62,13,10,60,47,102,111,114,109,62,13,10,60,112,62,255,8,60,47,112,62,13,10,60,47,99,101,110,116,101,114,62,13,10,60,47,98,111,100,121,62,13,10,60,47,104,116,109,108,62,13,10};

fs_file_t _web_interface_dot_html = {&_web_index_dot_html,0,1353,(simplefs_addr_t) &_data_web_interface_dot_html[0],{105,110,116,101,114,102,97,99,101,46,104,116,109,108,0}};

fs_dir_t _web = {NULL, NULL, &_web_interface_dot_html, {0}};

int web_server_dyn_expr(int exp, char *buf, int app_state, int connection_state)
{
  switch (exp) {
   case 3: return get_web_user_selection(buf,app_state,connection_state,1,2);
   case 6: return get_web_user_selection(buf,app_state,connection_state,0,4);
   case 7: return get_web_user_selection(buf,app_state,connection_state,1,4);
   case 0: return get_web_user_selection(buf,app_state,connection_state,0,1);
   case 5: return get_web_user_selection(buf,app_state,connection_state,1,3);
   case 4: return get_web_user_selection(buf,app_state,connection_state,0,3);
   case 2: return get_web_user_selection(buf,app_state,connection_state,0,2);
   case 8: return process_web_page_data(buf,app_state,connection_state);
   case 1: return get_web_user_selection(buf,app_state,connection_state,1,1);
  }
  return 0;
}

fs_dir_t *root = &_web;

