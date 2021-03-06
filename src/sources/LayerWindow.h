#ifndef LAYER_WINDOW_H
#define LAYER_WINDOW_H

#include <Application.h>
#include <Window.h>
#include <View.h>
#include <Invoker.h>
#include <Handler.h>
#include <ScrollView.h>
#include <MenuItem.h>
#include <MenuField.h>
#include <Slider.h>
#include <Bitmap.h>
#include <PictureButton.h>
#include <PopUpMenu.h>
#include <ListView.h>
#include <ListItem.h>
#include <TranslationUtils.h>
#include <stdio.h>

#include "ErrorCodes.h"
#include "SpLocaleApp.h"
#include "LayerWindowMsgs.h"
#include "TSlider.h"

#define LAYER_VIEW_HEIGHT 24
#define LAYER_TOP_HEIGHT 48

extern BWindow *bpmwindow;

class TriangleMenuView  : public BView 
{
public:
	TriangleMenuView (BRect r);
	virtual ~TriangleMenuView();

	virtual void Draw(BRect);
	virtual void MouseDown(BPoint point);

	BBitmap *img,*on,*off;
	BPopUpMenu* pm;
	
};


class LayerList: public BListView
{
public:
	LayerList(BRect frame,const char *name,int32 message,list_view_type type);
	~LayerList(void);
	void SelectionChanged(void);
	void AttachedToWindow(void);
	void PopulateList(int8 number_layers);
	void EmptyList(void);
	
	int32 selectionmsg;
	BInvoker *invoker;
};

class LayersView: public BView
{
public:
	LayersView(BRect frame);
	~LayersView(void);

	void Draw(BRect update_rect);	

	LayerList *visiblelist;
	BScrollView *scrollvisible;
	LayerList *activelist;
	BScrollView *scrollactive;
	
	void UpdateLayerStack(bool imagesopen);

	bool visible[255];
	int8 active_layer;
	int8 number_layers;
};

class LayerOptionsView  : public BView 
{
public:
	LayerOptionsView (BRect r);
	void AttachedToWindow(void);
//	void MessageReceived(BMessage *msg);
	void Draw(BRect r);
	
	TSlider *opacity;
	BMenuField *draw_mode; 
	TriangleMenuView *tmenu;
	BPictureButton *triangle_menu;
};

class LayerWindow : public BWindow 
{
public:
	LayerWindow(BRect frame, char *title);
	~LayerWindow();
	
	LayerOptionsView *options_view;
	LayersView	*layersview;
	
	bpm_status SetLayers(uint8 number,bool update_stack=false);
	bpm_status ShowLayer(uint8 index,bool update_stack=false);
	bpm_status HideLayer(uint8 index,bool update_stack=false);
	bpm_status SetActive(uint8 index,bool update_stack=false);
	bpm_status SetBlendMode(uint8 mode);
	bpm_status SetOpacity(uint8 value);
	void SetControlNotification(bool enabled);
	
	virtual void FrameMoved(BPoint origin);
	virtual void MessageReceived(BMessage *msg);
	BHandler *blackhole_handler;
	bool notify;
};

#endif