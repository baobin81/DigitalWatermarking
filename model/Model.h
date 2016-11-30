//
// Created by ilya on 13.11.16.
//

#ifndef WATERMARKENGINE_MODEL_H
#define WATERMARKENGINE_MODEL_H

#include <fstream>
#include <iostream>
#include "Watermark_Plugin.h"

struct Model{
    Watermark_Plugin* plugin;
    Model(){}
    virtual const char * embed(const char *msg_filename, const char *cover_filename, const char *stego_filename) {
        return plugin->embed(msg_filename, cover_filename, stego_filename);
    }

    virtual bool verify(const char *stego_filename, const char *orig_sig_data) {
        std::ifstream is(orig_sig_data);
        std::stringstream ss;
        plugin->extract(stego_filename, is, ss);
        double correlation = plugin->get_watermark_correlation(is, ss);
        return (correlation > plugin->get_high_watermark_level());
    }

    virtual const char* generate_signature(const char* pass, const char* file_name = NULL){
        if (file_name == NULL)
            file_name = "MySig.sig";
        plugin->generate_signature(pass, file_name);
        return file_name;
    }
    void setPlugin(Watermark_Plugin *plugin) {
        Model::plugin = plugin;
    }
};
#endif //WATERMARKENGINE_MODEL_H
