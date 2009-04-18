#ifndef DRAWRESOURCE_HH
#define DRAWRESOURCE_HH

class DrawResource
{
    public:

    virtual get_children(list<DrawResource*>& resources) {};

    virtual bool reusable() {return true;};

    virtual bool needs_depth_pass() { return false;};
    virtual void begin_depth_pass() {};
    virtual void end_depth_pass() {};

    virtual bool needs_full_pass() { return false;};
    virtual void begin_full_pass() {};
    virtual void end_full_pass() {};

    virtual ~DrawResource() {};
}

#endif
