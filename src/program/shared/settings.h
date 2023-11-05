#ifndef _SHAREDSETTINGS_X_UI_H
#define _SHAREDSETTINGS_X_UI_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	void *widget;
	int value;
	int min;
	int max;
	char digits;
	const char *fmt;
	bool odd;
} setting_decl;

void ui_setting_add(const char *name, setting_decl *opts);
void ui_setting_add_apply();

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

