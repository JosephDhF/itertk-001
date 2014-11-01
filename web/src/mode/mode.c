#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cgic.h"
#include "itscmd.h"
#include "mode.h"

char name[32]="";
CONFIG_MODE con_mode;


int session_read(char* name)
{
	char lsbuf[32]="";
	int ret = 0;
	sprintf(lsbuf, "/tmp/nc_%s", cgiRemoteAddr);
	int fd = open(lsbuf, O_RDONLY);
	if(fd <= 0)
		return 0;
	if(read(fd, name, 32) > 0)
		ret = 1;
	close(fd);
	return ret;
}


void show_workmode(void)
{
	char* wmode[] = {
		"�ر�",
		"TCP/UDP Socket"
	};
	
	fprintf(cgiOut, "				 <select name=\"workmode\" style=\"width:180px\">\n");
	int i;
	for(i = 0; i < 2; i++)
	{
		if(con_mode.mode == i)
			fprintf(cgiOut, "                      <option selected=\"selected\">%s</option>\n", wmode[i]);
		else
			fprintf(cgiOut, "                      <option>%s</option>\n", wmode[i]);
	}
	fprintf(cgiOut, "                    </select>\n");
}

void show_datamode(void)
{
	char* dmode[] = {
		"raw",
		"telnet"	
	};
	
	fprintf(cgiOut, "				 <select name=\"datamode\" style=\"width:100px\">\n");
	int i;
	for(i = 0; i < 2; i++)
	{
		if(con_mode.tcp_mode == i)
			fprintf(cgiOut, "                      <option selected=\"selected\">%s</option>\n", dmode[i]);
		else
			fprintf(cgiOut, "                      <option>%s</option>\n", dmode[i]);
	}
	fprintf(cgiOut, "                    </select>\n");
}


void show_session(int id)
{
	char* ptl[] = {
		"�ر�",
		"TCP Client",
		"TCP Server",
		"UDP"
	};
	fprintf(cgiOut, "					<td width=\"22%%\" height=\"30\" align=\"center\" bgcolor=\"#f2f2f2\" class=\"left_txt\"><select name=\"ptl%d\" style=\"width:180px\">\n", id);
	int i;
	for(i = 0; i < 4; i++)
	{
		if(con_mode.session[id].protocol == i)
			fprintf(cgiOut, "                      <option selected=\"selected\">%s</option>\n", ptl[i]);
		else
			fprintf(cgiOut, "                      <option>%s</option>\n", ptl[i]);
	}
	fprintf(cgiOut, "							</select></td>\n");
	fprintf(cgiOut, "					<td width=\"22%%\" height=\"30\" align=\"center\" bgcolor=\"#f2f2f2\" class=\"left_txt\"><input type=\"text\" name=\"ip%d\" value=\"%s\" size=\"30\" /></td>\n", id, sys_ip2str_static(con_mode.session[id].ip));
	fprintf(cgiOut, "					<td width=\"22%%\" height=\"30\" align=\"center\" bgcolor=\"#f2f2f2\" class=\"left_txt\"><input type=\"text\" name=\"lport%d\" value=\"%d\" size=\"30\" /></td>\n",id, con_mode.session[id].lport);
	fprintf(cgiOut, "					 <td width=\"22%%\" height=\"30\" align=\"center\" bgcolor=\"#f2f2f2\" class=\"left_txt\"><input type=\"text\" name=\"dport%d\" value=\"%d\" size=\"30\" /></td>\n", id, con_mode.session[id].dport);
}



void get_workmode(void)
{
	char* wmode[] = {
		"�ر�",
		"TCP/UDP Socket"
	};
	int i;
	cgiFormSelectSingle("workmode", wmode, sizeof(wmode)/sizeof(wmode[0]), &i, 0);
	con_mode.mode = i;
}

void get_datamode(void)
{
	char* dmode[] = {
		"raw",
		"telnet"	
	};
	int i;
	cgiFormSelectSingle("datamode", dmode, sizeof(dmode)/sizeof(dmode[0]), &i, 0);
	con_mode.tcp_mode= i;
}



void get_input(char* str, char* dp)
{
	bzero(dp, 32);
	cgiFormStringNoNewlines(str, dp, 30);
}


void get_session(int id)
{
	char* ptl[] = {
		"�ر�",
		"TCP Client",
		"TCP Server",
		"UDP"
	};
	int i;
	char lsbuf[32]="";
	sprintf(lsbuf, "ptl%d", id);
	cgiFormSelectSingle(lsbuf, ptl, sizeof(ptl)/sizeof(ptl[0]), &i, 0);
	con_mode.session[id].protocol = i;

	bzero(lsbuf, 32);
	sprintf(lsbuf, "ip%d", id);
	char str[32]="";
	get_input(lsbuf, str);
	con_mode.session[id].ip = sys_str2ip(str);
	
	bzero(lsbuf, 32);
	sprintf(lsbuf, "lport%d", id);
	bzero(str, 32);
	get_input(lsbuf, str);
	con_mode.session[id].lport = atoi(str);

	bzero(lsbuf, 32);
	sprintf(lsbuf, "dport%d", id);
	bzero(str, 32);
	get_input(lsbuf, str);
	con_mode.session[id].dport = atoi(str);	

	
}

int cgiMain()
{
	int ret = session_read(name);
	if(ret != 1)
	{
		cgiHeaderContentType("text/html;charset=gb2312");
		fprintf(cgiOut, "<HTML><HEAD>\n");
		fprintf(cgiOut,	"</HEAD><BODY>\n");
		fprintf(cgiOut, "<script type=\"text/javascript\">\n");
		fprintf(cgiOut, "window.alert(\"�û���δ��¼�������µ�¼(�����룺%d)��\");\n", ret);
		fprintf(cgiOut, "window.location.href=\"../login.html\";\n");
		fprintf(cgiOut, "</script>\n");
		fprintf(cgiOut, "</BODY>\n");
		fprintf(cgiOut, "</HTML>\n");
		return 0;
	}

	int id = atoi(cgiQueryString);
	con_mode.id = id;
	ret = its_conf_mode_query(name, &con_mode);
	
	cgiHeaderContentType("text/html;charset=gb2312");
	fprintf(cgiOut, "<style type=\"text/css\">\n");
	fprintf(cgiOut, "<!--\n");
	fprintf(cgiOut, "body {\n");
	fprintf(cgiOut, "	margin-left: 0px;\n");
	fprintf(cgiOut, "	margin-top: 0px;\n");
	fprintf(cgiOut, "	margin-right: 0px;\n");
	fprintf(cgiOut, "	margin-bottom: 0px;\n");
	fprintf(cgiOut, "	background-color: #F8F9FA;\n");
	fprintf(cgiOut, "}\n");
	fprintf(cgiOut, "-->\n");
	fprintf(cgiOut, "</style>\n");
	fprintf(cgiOut, "<link href=\"../images/skin.css\" rel=\"stylesheet\" type=\"text/css\" />\n");
	fprintf(cgiOut, "<body>\n");
	
	if(ret != QUERY_OK)
	{
		fprintf(cgiOut, "<script type=\"text/javascript\">\n");
		fprintf(cgiOut, "window.alert(\"(�����룺%d)��\");\n", ret);
		fprintf(cgiOut, "</script>\n");		
	}
	else if(cgiFormSubmitClicked("mode") == cgiFormSuccess)
	{

		get_workmode();
		get_datamode();
		int i;
		for(i = 0; i < 6; i++)
			get_session(i);
		
		ret = its_conf_mode_set(name, &con_mode);
		if(ret != MODE_SET_OK)
		{
			fprintf(cgiOut, "<script type=\"text/javascript\">\n");
			fprintf(cgiOut, "window.alert(\"�ύʧ��(�����룺%d)��\");\n", ret);
			fprintf(cgiOut, "</script>\n");
			
			//�ύʧ�ܺ���Ҫ���»�ȡ����
			bzero(&con_mode, sizeof(con_mode));
			con_mode.id = id;
			its_conf_mode_query(name, &con_mode);
		}
		else
		{
			fprintf(cgiOut, "<script type=\"text/javascript\">\n");
			fprintf(cgiOut, "window.alert(\"�ύ�ɹ���\");\n");
			fprintf(cgiOut, "</script>\n");
		}
	}
	
	
fprintf(cgiOut, "<table width=\"100%%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\n");
fprintf(cgiOut, "	<tr>\n");
fprintf(cgiOut, "	  <td width=\"17\" height=\"29\" valign=\"top\" background=\"../images/mail_leftbg.gif\"><img src=\"../images/left-top-right.gif\" width=\"17\" height=\"29\" /></td>\n");
fprintf(cgiOut, "	 <td width=\"935\" height=\"29\" valign=\"top\" background=\"../images/content-bg.gif\"><table width=\"100%%\" height=\"31\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" class=\"left_topbg\" id=\"table2\">\n");
fprintf(cgiOut, " 	 <tr>\n");
fprintf(cgiOut, " 	   <td height=\"31\"><div class=\"titlebt\">ģʽ����</div></td>\n");
fprintf(cgiOut, "	   </tr>\n");
fprintf(cgiOut, "	  </table></td>\n");
fprintf(cgiOut, "	 <td width=\"16\" valign=\"top\" background=\"../images/mail_rightbg.gif\"><img src=\"../images/nav-right-bg.gif\" width=\"16\" height=\"29\" /></td>\n");
fprintf(cgiOut, "  </tr>\n");
fprintf(cgiOut, "	<tr>\n");
fprintf(cgiOut, "	  <td height=\"71\" valign=\"middle\" background=\"../images/mail_leftbg.gif\">&nbsp;</td>\n");
fprintf(cgiOut, "	 <td valign=\"top\" bgcolor=\"#F7F8F9\"><table width=\"100%%\" height=\"138\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\n");
fprintf(cgiOut, "	  <tr>\n");
fprintf(cgiOut, "		<td height=\"13\" valign=\"top\">&nbsp;</td>\n");
fprintf(cgiOut, "		</tr>\n");
fprintf(cgiOut, " 	 <tr>\n");
fprintf(cgiOut, " 	   <td valign=\"top\"><table width=\"98%%\" border=\"0\" align=\"center\" cellpadding=\"0\" cellspacing=\"0\">\n");
fprintf(cgiOut, " 		 <tr>\n");
fprintf(cgiOut, " 		   <td class=\"left_txt\">��ǰλ�ã�ģʽ����</td>\n");
fprintf(cgiOut, " 		 </tr>\n");
fprintf(cgiOut, "		  <tr>\n");
fprintf(cgiOut, "			<td height=\"20\"><table width=\"100%%\" height=\"1\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" bgcolor=\"#CCCCCC\">\n");
fprintf(cgiOut, "			  <tr>\n");
fprintf(cgiOut, "				<td></td>\n");
fprintf(cgiOut, " 			 </tr>\n");
fprintf(cgiOut, "			</table></td>\n");
fprintf(cgiOut, " 		 </tr>\n");
fprintf(cgiOut, "		  <tr>\n");
fprintf(cgiOut, "			<td><table width=\"100%%\" height=\"55\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\n");
fprintf(cgiOut, " 			 <tr>\n");
fprintf(cgiOut, " 			   <td width=\"10%%\" height=\"55\" valign=\"middle\"><img src=\"../images/title.gif\" width=\"54\" height=\"55\"></td>\n");
fprintf(cgiOut, "				 <td width=\"90%%\" valign=\"top\"><span class=\"left_txt2\">����������Ը�������Ҫ���޸������豸��</span><span class=\"left_txt3\">����ģʽ</span><span class=\"left_txt2\">��</span><br>\n");
fprintf(cgiOut, " 						 <span class=\"left_txt2\">����</span><span class=\"left_txt3\">����ģʽ������ģʽ��Э�飬�˿�</span><span class=\"left_txt2\">�Ȳ���</span><span class=\"left_txt3\"></span><span class=\"left_txt2\">�� </span></td>\n");
fprintf(cgiOut, "			  </tr>\n");
fprintf(cgiOut, "			 </table></td>\n");
fprintf(cgiOut, "		  </tr>\n");
fprintf(cgiOut, "		   <tr>\n");
fprintf(cgiOut, "			 <td>&nbsp;</td>\n");
fprintf(cgiOut, "			</tr>\n");
fprintf(cgiOut, " 		 <tr>\n");
fprintf(cgiOut, " 		   <td><table width=\"100%%\" height=\"31\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" class=\"nowtable\">\n");
fprintf(cgiOut, "			   <tr>\n");
fprintf(cgiOut, "				 <td class=\"left_bt2\">&nbsp;&nbsp;&nbsp;&nbsp;�˿�%d����</td>\n", con_mode.id);
fprintf(cgiOut, " 			 </tr>\n");
fprintf(cgiOut, "			</table></td>\n");
fprintf(cgiOut, " 		 </tr>\n");
fprintf(cgiOut, "		  <tr>\n");
fprintf(cgiOut, "			<td><table width=\"100%%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">\n");
fprintf(cgiOut, "			   <form name=\"form1\" method=\"POST\" action=\"");
fprintf(cgiOut, "\">\n");

fprintf(cgiOut, "			   <tr>\n");
fprintf(cgiOut, "				 <td width=\"20%%\" height=\"30\" align=\"right\" bgcolor=\"#f2f2f2\" class=\"left_txt2\">����ģʽ��</td>\n");
fprintf(cgiOut, "				 <td width=\"3%%\" bgcolor=\"#f2f2f2\">&nbsp;</td>\n");
fprintf(cgiOut, " 			   <td width=\"32%%\" height=\"30\" bgcolor=\"#f2f2f2\">\n");
show_workmode();

fprintf(cgiOut, "							</td>\n");
fprintf(cgiOut, "				<td width=\"45%%\" height=\"30\" bgcolor=\"#f2f2f2\" class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, "			  </tr>\n");
fprintf(cgiOut, "			   <tr>\n");
fprintf(cgiOut, "				 <td height=\"30\" align=\"right\" class=\"left_txt2\">TCP����ģʽ��</td>\n");
fprintf(cgiOut, " 			   <td>&nbsp;</td>\n");
fprintf(cgiOut, "				<td height=\"30\">\n");
show_datamode();

fprintf(cgiOut, "							</td>\n");
fprintf(cgiOut, "				<td height=\"30\" class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, "				</tr>\n");
fprintf(cgiOut, " 			 <tr>\n");
fprintf(cgiOut, " 			   <td height=\"17\" colspan=\"4\" align=\"right\" >&nbsp;</td>\n");
fprintf(cgiOut, "			   </tr>\n");
fprintf(cgiOut, "				<tr>\n");
fprintf(cgiOut, "				  <td height=\"30\" colspan=\"4\" align=\"right\" class=\"left_txt2\"><table width=\"100%%\" height=\"31\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" class=\"nowtable\">\n");
fprintf(cgiOut, "				  <tr>\n");
fprintf(cgiOut, "					<td class=\"left_bt2\">&nbsp;&nbsp;&nbsp;&nbsp;�Ự</td>\n");
fprintf(cgiOut, "					</tr>\n");
fprintf(cgiOut, " 			   </table></td>\n");
fprintf(cgiOut, "				</tr>\n");
fprintf(cgiOut, " 			 <tr>\n");
fprintf(cgiOut, " 			   <td height=\"30\" colspan=\"4\" class=\"left_txt2\"><table width=\"100%%\" height=\"99\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\n");
fprintf(cgiOut, "			<tr>\n");
fprintf(cgiOut, "			 <td width=\"12%%\" height=\"30\" align=\"right\" bgcolor=\"#f2f2f2\" class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, "			 <td width=\"22%%\" height=\"30\" align=\"center\" bgcolor=\"#f2f2f2\" class=\"left_txt\">Э��</td>\n");
fprintf(cgiOut, "			 <td width=\"22%%\" height=\"30\" align=\"center\" bgcolor=\"#f2f2f2\" class=\"left_txt\">�Զ�����</td>\n");
fprintf(cgiOut, "			 <td width=\"22%%\" height=\"30\" align=\"center\" bgcolor=\"#f2f2f2\" class=\"left_txt\">�����˿�</td>\n");
fprintf(cgiOut, "					<td width=\"22%%\" height=\"30\" align=\"center\" bgcolor=\"#f2f2f2\" class=\"left_txt\">�Զ˶˿�</td>\n");
fprintf(cgiOut, "			</tr>				   <tr>\n");
fprintf(cgiOut, "					 <td width=\"12%%\" height=\"30\" align=\"right\" bgcolor=\"#f2f2f2\" class=\"left_txt\">��						 </td>\n");
show_session(0);

fprintf(cgiOut, " 				 </tr>\n");
fprintf(cgiOut, "				  <tr>\n");
fprintf(cgiOut, "					<td width=\"12%%\" height=\"30\" align=\"right\" bgcolor=\"#f2f2f2\" class=\"left_txt\">��</td>\n");
show_session(1);
fprintf(cgiOut, " 				 </tr>\n");
fprintf(cgiOut, "				  <tr>\n");
fprintf(cgiOut, "					<td width=\"12%%\" height=\"30\" align=\"right\" bgcolor=\"#f2f2f2\" class=\"left_txt\">��</td>\n");
show_session(2);
fprintf(cgiOut, "				  </tr>\n");
fprintf(cgiOut, "				   <tr>\n");
fprintf(cgiOut, "					 <td width=\"12%%\" height=\"30\" align=\"right\" bgcolor=\"#f2f2f2\" class=\"left_txt\">��</td>\n");
show_session(3);
fprintf(cgiOut, " 				 </tr>\n");
fprintf(cgiOut, "				  <tr>\n");
fprintf(cgiOut, "					<td width=\"12%%\" height=\"30\" align=\"right\" bgcolor=\"#f2f2f2\" class=\"left_txt\">��</td>\n");
show_session(4);
fprintf(cgiOut, "				   </tr>\n");
fprintf(cgiOut, "				<tr>\n");
fprintf(cgiOut, "					  <td width=\"12%%\" height=\"30\" align=\"right\" bgcolor=\"#f2f2f2\" class=\"left_txt\">��</td>\n");
show_session(5);
fprintf(cgiOut, " 				 </tr>					<tr>\n");
fprintf(cgiOut, "					  <td colspan=\"3\" align=\"right\">&nbsp;</td>\n");
fprintf(cgiOut, "				   </tr>\n");
fprintf(cgiOut, "				  </table></td>\n");
fprintf(cgiOut, "			   </tr>\n");
fprintf(cgiOut, "				<tr>\n");
fprintf(cgiOut, "				  <td height=\"30\" colspan=\"4\" class=\"left_txt\"><table width=\"100%%\" height=\"90\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\">\n");
fprintf(cgiOut, "				  <tr>\n");
fprintf(cgiOut, "					<td width=\"27%%\" align=\"center\" bgcolor=\"#f2f2f2\" class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, " 				   <td width=\"27%%\" bgcolor=\"#f2f2f2\" class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, "					 <td width=\"24%%\" bgcolor=\"#f2f2f2\" class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, " 				   <td width=\"22%%\" bgcolor=\"#f2f2f2\" class=\"left_txt\"><span class=\"left_txt2\">\n");
fprintf(cgiOut, "					  <input type=\"submit\" value=\"��������޸�\" name=\"mode\" />\n");
fprintf(cgiOut, "					</span></td>\n");
fprintf(cgiOut, "					</tr>\n");
fprintf(cgiOut, " 				 <tr>\n");
fprintf(cgiOut, " 				   <td align=\"center\" class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, "					<td class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, "					<td class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, "					<td class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, "				  </tr>\n");
fprintf(cgiOut, "				   <tr>\n");
fprintf(cgiOut, "					 <td align=\"center\" bgcolor=\"#f2f2f2\" class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, "					  <td bgcolor=\"#f2f2f2\" class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, "					  <td bgcolor=\"#f2f2f2\" class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, "					  <td bgcolor=\"#f2f2f2\" class=\"left_txt\">&nbsp;</td>\n");
fprintf(cgiOut, "					</tr>\n");
fprintf(cgiOut, " 			   </table></td>\n");
fprintf(cgiOut, "				  </tr>\n");
fprintf(cgiOut, "			 </table></td>\n");
fprintf(cgiOut, "		  </tr>\n");
fprintf(cgiOut, "		 </table>\n");
fprintf(cgiOut, " 		 <table width=\"100%%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\">\n");
fprintf(cgiOut, "			  <tr>\n");
fprintf(cgiOut, "			  <td colspan=\"3\">&nbsp;</td>\n");
fprintf(cgiOut, "			 </tr>\n");
fprintf(cgiOut, "			<tr>\n");
fprintf(cgiOut, "			   <td height=\"30\" colspan=\"3\">&nbsp;</td>\n");
fprintf(cgiOut, "			</tr>\n");
fprintf(cgiOut, " 		   \n");
fprintf(cgiOut, "			 <tr>\n");
fprintf(cgiOut, " 			 <td height=\"30\" colspan=\"3\">&nbsp;</td>\n");
fprintf(cgiOut, "			  </tr>\n");
fprintf(cgiOut, "			 <tr>\n");
fprintf(cgiOut, " 			 <td width=\"50%%\" height=\"30\" align=\"right\">&nbsp;</td>\n");
fprintf(cgiOut, "				<td width=\"6%%\" height=\"30\" align=\"right\">&nbsp;</td>\n");
fprintf(cgiOut, "			  <td width=\"44%%\" height=\"30\">&nbsp;</td>\n");
fprintf(cgiOut, " 		   </tr>\n");
fprintf(cgiOut, "			  <tr>\n");
fprintf(cgiOut, "			  <td height=\"30\" colspan=\"3\">&nbsp;</td>\n");
fprintf(cgiOut, " 		   </tr>\n");
fprintf(cgiOut, "			</table></td>\n");
fprintf(cgiOut, " 	 </tr>\n");
fprintf(cgiOut, "	</table></td>\n");
fprintf(cgiOut, "    <td background=\"../images/mail_rightbg.gif\">&nbsp;</td>\n");
fprintf(cgiOut, "  </tr>\n");
fprintf(cgiOut, "  <tr>\n");
fprintf(cgiOut, "	<td valign=\"middle\" background=\"../images/mail_leftbg.gif\"><img src=\"../images/buttom_left2.gif\" width=\"17\" height=\"17\" /></td>\n");
fprintf(cgiOut, "	   <td height=\"17\" valign=\"top\" background=\"../images/buttom_bgs.gif\"><img src=\"../images/buttom_bgs.gif\" width=\"17\" height=\"17\" /></td>\n");
fprintf(cgiOut, "	<td background=\"../images/mail_rightbg.gif\"><img src=\"../images/buttom_right2.gif\" width=\"16\" height=\"17\" /></td>\n");
fprintf(cgiOut, "  </tr>\n");
fprintf(cgiOut, "</table>\n");
	fprintf(cgiOut, "</body>\n");
}



