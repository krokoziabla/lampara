#include <alsa/asoundlib.h>
#include <glib.h>
#include <string.h>

#include "package.h"

SndCardDesc * enumerate_sound_cards(int * result_length)
{
    g_return_val_if_fail(result_length != NULL, NULL);

    *result_length = 0;

    void ** hints;

    if ( snd_device_name_hint(-1, "pcm", &hints) )
    {
        g_printerr ("Couldn't load the list of sound cards\n");
        return NULL;
    }

    for ( void ** hint = hints; *hint != NULL; ++hint )
    {
        ++*result_length;
    }

    SndCardDesc * card_descs = g_new(SndCardDesc, *result_length),
                * card_desc = card_descs;

    for ( void ** hint = hints; *hint != NULL; ++hint )
    {
        card_desc->name = g_strdup(snd_device_name_get_hint(*hint, "NAME"));
        card_desc->desc = g_strdup(snd_device_name_get_hint(*hint, "DESC"));
        card_desc->ioid = g_strdup(snd_device_name_get_hint(*hint, "IOID"));

        ++card_desc;
    }

    snd_device_name_free_hint(hints);

    return card_descs;
}
