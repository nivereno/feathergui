// Copyright �2016 Black Sphere Studios
// For conditions of distribution and use, see copyright notice in "feathergui.h"

#include "fgProgressbar.h"
#include "fgSkin.h"
#include "feathercpp.h"

fgElement* FG_FASTCALL fgProgressbar_Create(FREL value, fgElement* BSS_RESTRICT parent, fgElement* BSS_RESTRICT next, const char* name, fgFlag flags, const fgTransform* transform)
{
  fgElement* r = fgCreate("Progressbar", parent, next, name, flags, transform);
  _sendmsg<FG_SETVALUE, float>(r, value);
  return r;
}

void FG_FASTCALL fgProgressbar_Init(fgProgressbar* BSS_RESTRICT self, fgElement* BSS_RESTRICT parent, fgElement* BSS_RESTRICT next, const char* name, fgFlag flags, const fgTransform* transform)
{
  fgElement_InternalSetup(*self, parent, next, name, flags, transform, (fgDestroy)&fgProgressbar_Destroy, (fgMessage)&fgProgressbar_Message);
}

void FG_FASTCALL fgProgressbar_Destroy(fgProgressbar* self)
{
  fgControl_Destroy(&self->control);
}

size_t FG_FASTCALL fgProgressbar_Message(fgProgressbar* self, const FG_Msg* msg)
{
  static const fgTransform BAR_ELEMENT = { 0,0,0,0,0,0,0,1.0,0,0,0,0,0 };

  assert(self != 0 && msg != 0);
  switch(msg->type)
  {
  case FG_CONSTRUCT:
    fgControl_Message(&self->control, msg);
    fgElement_Init(&self->bar, *self, 0, "Progressbar$bar", FGELEMENT_BACKGROUND | FGELEMENT_IGNORE, &BAR_ELEMENT);
    fgText_Init(&self->text, *self, 0, "Progressbar$text", FGELEMENT_EXPAND | FGELEMENT_IGNORE, &fgTransform_CENTER);
    self->value = 0.0f;
    return FG_ACCEPT;
  case FG_ADDITEM:
    if(msg->other)
      _sendmsg<FG_ADDCHILD, void*>(&self->bar, msg->other);
    else
      fgElement_Clear(&self->bar);
    return FG_ACCEPT;
  case FG_SETVALUE:
    if(msg->subtype <= FGVALUE_FLOAT)
    {
      float value = (msg->subtype == FGVALUE_INT64) ? (float)msg->otherint : msg->otherf;
      if(value != self->value)
      {
        self->value = value;
        CRect area = self->bar.transform.area;
        area.right.rel = self->value;
        _sendmsg<FG_SETAREA, void*>(&self->bar, &area);
      }
      return FG_ACCEPT;
    }
    return 0;
  case FG_GETVALUE:
    if(!msg->subtype || msg->subtype == FGVALUE_FLOAT)
      return *reinterpret_cast<size_t*>(&self->value);
    if(msg->subtype == FGVALUE_INT64)
      return (size_t)self->value;
    return 0;
  case FG_SETTEXT:
  case FG_SETFONT:
  case FG_SETLINEHEIGHT:
  case FG_SETLETTERSPACING:
  case FG_SETCOLOR:
  case FG_GETTEXT:
  case FG_GETFONT:
  case FG_GETLINEHEIGHT:
  case FG_GETLETTERSPACING:
  case FG_GETCOLOR:
    return fgPassMessage(self->text, msg);
  case FG_GETCLASSNAME:
    return (size_t)"Progressbar";
  }
  return fgControl_Message(&self->control, msg);
}
