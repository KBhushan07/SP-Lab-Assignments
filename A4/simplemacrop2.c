#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
		FILE *f1, *f2, *f3, *f4;
		char label[100], code[100], operand[100], du_label[100], du_code[100], du_operand[100], ala[100];
		int mntc, mdtc, i = 0, j = 0, k = 0, flag = 0;
		
		f1 = fopen ("output_file2.txt","w");
		f2 = fopen ("mnt_table.txt","r");
		f3 = fopen ("mdt_table.txt","r");
		f4 = fopen ("output_file1.txt","r");
		
		while (fscanf (f4,"%s%s%s",label,code,operand) != EOF)
		{
			while (fscanf (f2,"%d%s%s%s%d",&mntc,du_label,du_code,du_operand,&mdtc) != EOF) // searching in mnt_table for match
				if ( strcmp (code,du_code) == 0)
				{
					flag = 1; 
					break;
				}
			if (flag == 1)
			{   
				i = 0;
				j = 0;
				while ( operand[i] != '\0' )
				{
					ala[j ++] = operand[i ++];
					if (operand[i] == ',')
					{
						i ++;
						ala[j ++] = ' ';
					}
				}
				ala[j] = ' ';
				for (i = 1; i <= mdtc; i ++)
						fscanf (f3,"%d%s%s%s",&j,du_label,du_code,du_operand);
				while ( !(strcmp (du_code,"MEND") == 0) )
				{
					fscanf (f3,"%d%s%s%s",&mdtc,du_label,du_code,du_operand); 
					i = 0;
					while ( du_operand[i] != '\0' )
					{  
						if ( du_operand[i] == '#' )
						{
							k = ((int) du_operand[i + 1]) - 48;
							j = 0;
							while (k != 0)
							{
								if (ala[j] == ' ')
									k = k - 1;
								j = j + 1;
							}
							while (ala[j] != ' ')
								du_operand[i ++] = ala[j ++];
							du_operand[i] = '\0';
						}
						else
							i ++;				
					}
					if ( !(strcmp (du_code,"MEND") == 0) )
						fprintf (f1,"%s\t%s\t%s\n",du_label,du_code,du_operand);
				}
			}
			else
				fprintf (f1,"%s\t%s\t%s\n",label,code,operand);
			flag = 0;
			fseek (f2,0,SEEK_SET);
			fseek (f3,0,SEEK_SET);
	 	}
}