#include "game.h"
#include "entities/playerstart.h"

namespace game
{
    // Global player entity pointer.
    entities::classes::BaseEntity *player1 = NULL;

    // Networking State properties.
    bool connected = false;

    // Map Game State properties.
    int maptime = 0;
    cubestr mapname = "";

    void updateworld()
    {
        // Update the world time.
        if(!maptime) {
            maptime = lastmillis;
            return;
        }

        // Escape this function if there is no currenttime. (Meaning it is 0.)
        if(!curtime) return;

        // Update the physics.
        physicsframe();

        // Update all our objects.
        updateentities();
    }

    void updateentities() {
        // Execute think actions for entities.
        loopv(entities::ents)
        {
            // Let's go at it!
            entities::classes::BaseEntity *e = entities::ents[i];
            e->think();
//          if(e.type == ENT_PLAYER) {}
        }

        // Player specific think action.
        player1->think();
    }

    void gameconnect(bool _remote)
    {
        // Store connection state.
        connected = true;

        // Toggle edit mode if required.
        if(editmode)
            toggleedit();
    }

    void gamedisconnect(bool cleanup)
    {
        // Disconnected.
        connected = false;
    }

    void changemap(const char *name)
    {
        // Are we connected? If not, connect locally.
        if(!connected) localconnect();

        // Toggle edit mode if required.
        if(editmode)
            toggleedit();

        // If world loading fails, start a new empty map instead.
        if(!load_world(name))
            emptymap(0, true, name);
    }

    void forceedit(const char *name)
    {
        // Trigger a changemap by force edit, which in return toggles edit mode.
        changemap(name);
    }

    ICOMMAND(map, "s", (char *s), changemap(s));

    // Never seen an implementation of this function, should be part of BaseEntity.
    void dynentcollide(physent *d, physent *o, const vec &dir) {}

    // Never seen an implementation of this function, should be part of BaseEntity.
    void bounced(physent *d, const vec &surface) {}

    // Unsure what to do with these yet.
    void edittrigger(const selinfo &sel, int op, int arg1, int arg2, int arg3, const VSlot *vs) {

    }
    void vartrigger(ident *id) {

    }

    // These speak for themselves.
    const char *getclientmap() {
        return mapname;
    }
    const char *getmapinfo() {
        return NULL;
    }
    void resetgamestate() {

    }
    void suicide(physent *d) {

    }
    void newmap(int size) {

    }
    void loadingmap(const char *name) {
    }

    void startmap(const char *name)
    {
        // Copy into mapname and reset maptime.
        copycubestr(mapname, name ? name : "");
        maptime = 0;

        // Find our playerspawn.
        findplayerspawn(player1);
    }

    bool needminimap() {
        return false;
    }

    float abovegameplayhud(int w, int h)
    {
        switch(player1->state)
        {
            case CS_EDITING:
                return 1;
            default:
                return (h-min(128, h))/float(h);
        }
    }

    void gameplayhud(int w, int h)
    {

    }

    float clipconsole(float w, float h) {
        return 0;
    }

    void preload() {
        entities::preloadentities();
    }

    void renderavatar() {

    }

    void renderplayerpreview(int model, int team, int weap) {

    }

    bool canjump() {
        return true;
    }
    bool cancrouch() {
        if(!connected) return false;
        return player1->state!=CS_DEAD;
    }

    bool allowmove(physent *d) {
        return true;
        //if(d->type!=ENT_PLAYER) return true;
        //else return false;
        //if(d->type!=ENT_PLAYER) return true;

        // Checks whether the entity(usually a client/player) has done anything that requires waiting time.
        //return !((entities::classes::BaseEntity *)d)->lasttaunt || lastmillis-((entities::classes::BaseEntity *)d)->lasttaunt>=1000;
    }

    dynent *iterdynents(int i) {
        // TODO: Fix this, objects should be the ents array I guess.
        // Reference is found in fps code.
//        dynent *iterdynents(int i)
//        {
//            if(i<players.length()) return players[i];
//            i -= players.length();
//            if(i<monsters.length()) return (dynent *)monsters[i];
//            i -= monsters.length();
//            if(i<movables.length()) return (dynent *)movables[i];
//            return NULL;
//        }
        return player1;
    }
    // int numdynents() { return players.length()+monsters.length()+movables.length(); }
    int numdynents() {
        return 1;
    }

    void rendergame(bool mainpass) {
         // TODO: Fix this.
        //if(isthirdperson()) renderclient(player1, "ogro", NULL, 0, ANIM_ATTACK1, 300, player1->lastaction, player1->lastpain);

        // Loop through our entities and render them all.

    }

    const char *defaultcrosshair(int index) {
        return "data/crosshair.png";
    }

    int selectcrosshair(vec &color) {
        if(player1->state==CS_DEAD) return -1;
        return 0;
    }

    void setupcamera() {
    }

    bool allowthirdperson() {
        return true;
    }

    bool detachcamera() {
        return player1->state==CS_DEAD;
    }

    bool collidecamera() {
        return player1->state!=CS_EDITING;
    }

    void lighteffects(dynent *e, vec &color, vec &dir) {
    }

    void adddynlights() {
    }

    void dynlighttrack(physent *owner, vec &o, vec &hud) {
    }

    void particletrack(physent *owner, vec &o, vec &d) {
    }

    void writegamedata(vector<char> &extras) {

    }
    void readgamedata (vector<char> &extras) {

    }

    const char *gameconfig() { return "config/game.cfg"; }
    const char *savedconfig() { return "config/saved.cfg"; }
    const char *restoreconfig() { return "config/restore.cfg"; }
    const char *defaultconfig() { return "config/default.cfg"; }
    const char *autoexec() { return "config/autoexec.cfg"; }
    const char *savedservers() { return "config/servers.cfg"; }

    void loadconfigs() {
        execfile("config/auth.cfg", false);
    }

    void parseoptions(vector<const char *> &args) {}
    void connectattempt(const char *name, const char *password, const ENetAddress &address) {}
    void connectfail() {}
    void parsepacketclient(int chan, packetbuf &p) {}
    bool allowedittoggle() { return true; }
    void edittoggled(bool on) {}
    void writeclientinfo(stream *f) {}
    void toserver(char *text) {}
    bool ispaused() { return false; }
    int scaletime(int t) { return t*100; }
    bool allowmouselook() { return true; }

    //---------------------------------------------------------------

    void physicstrigger(physent *d, bool local, int floorlevel, int waterlevel, int material)
    {
        // This function seems to be used for playing material audio. No worries about that atm.
/*        if     (waterlevel>0) { if(material!=MAT_LAVA) playsound(S_SPLASHOUT, d==player1 ? NULL : &d->o); }
        else if(waterlevel<0) playsound(material==MAT_LAVA ? S_BURN : S_SPLASHIN, d==player1 ? NULL : &d->o);
        if     (floorlevel>0) { if(d==player1 || d->type!=ENT_PLAYER || ((gameent *)d)->ai) msgsound(S_JUMP, d); }
        else if(floorlevel<0) { if(d==player1 || d->type!=ENT_PLAYER || ((gameent *)d)->ai) msgsound(S_LAND, d); }*/
    }

    void initclient() {
        // This may work.
        // TODO: It may fail lol.
        player1 = new entities::classes::PlayerStart();
        player1->setspawned(true);
    }

    const char *gameident() {
        return "SchizoMania";
    }
    const char *getscreenshotinfo() {
        return NULL;
    }

}; // namespace game.


