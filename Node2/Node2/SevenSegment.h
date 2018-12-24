#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

void		SEGDISP_Init();
void		SEGDISP_SetInteger(int number);
void		SEGDISP_SetFloat(float number, unsigned char decimals);
void		SEGDISP_Clear();
void		SEGDISP_Refresh();

#endif