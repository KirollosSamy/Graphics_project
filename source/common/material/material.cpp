#include "material.hpp"

#include "../asset-loader.hpp"
#include "deserialize-utils.hpp"

/*Materialclass represents a basic material that can be used to render objects in the game engine.
It contains a PipelineState object that holds information about the rendering pipeline
and a ShaderProgram object that holds the shader code for rendering.
The setup() function sets up the pipeline state and uses the shader program.*/

namespace our
{

    // This function should setup the pipeline state and set the shader to be used
    void Material::setup() const
    {
        // TODO: (Req 7) Write this function
        pipelineState.setup();
        shader->use();
    }

    // This function read the material data from a json object
    void Material::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;

        if (data.contains("pipelineState"))
        {
            pipelineState.deserialize(data["pipelineState"]);
        }
        shader = AssetLoader<ShaderProgram>::get(data["shader"].get<std::string>());
        transparent = data.value("transparent", false);
    }

    // This function should call the setup of its parent and
    // set the "tint" uniform to the value in the member variable tint

    /*TintedMaterial class extends Material and
    adds a glm::vec4 variable tint that represents the color tint to be applied to the object.
    The setup() function first calls the Material::setup() function to set up the pipeline state and use the shader program,
    then it sets the tint uniform in the shader program.*/
    void TintedMaterial::setup() const
    {
        // TODO: (Req 7) Write this function
        Material::setup();
        shader->set("tint", tint);
    }

    // This function read the material data from a json object
    void TintedMaterial::deserialize(const nlohmann::json &data)
    {
        Material::deserialize(data);
        if (!data.is_object())
            return;
        tint = data.value("tint", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // This function should call the setup of its parent and
    // set the "alphaThreshold" uniform to the value in the member variable alphaThreshold
    // Then it should bind the texture and sampler to a texture unit and send the unit number to the uniform variable "tex"

    /*TexturedMaterial class extends TintedMaterial and adds a Texture2D object and a Sampler object for texturing the object.
     The setup() function first calls the TintedMaterial::setup() function to set up the tint and pipeline state,
     then it sets the alphaThreshold uniform in the shader program and binds the texture and sampler to a texture unit.*/
    void TexturedMaterial::setup() const
    {
        // TODO: (Req 7) Write this function
        TintedMaterial::setup();
        shader->set("alphaThreshold", alphaThreshold);

        glActiveTexture(GL_TEXTURE0);

        if (texture)
            texture->bind();

        if (sampler)
            sampler->bind(0);
        shader->set("tex", 0);
    }

    // This function read the material data from a json object
    void TexturedMaterial::deserialize(const nlohmann::json &data)
    {
        TintedMaterial::deserialize(data);
        if (!data.is_object())
            return;
        alphaThreshold = data.value("alphaThreshold", 0.0f);
        texture = AssetLoader<Texture2D>::get(data.value("texture", ""));
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }

}
/*
deserialize() function that reads the material data from a JSON object.
These functions check for the existence of certain keys in the JSON object,
such as pipelineState, shader, transparent, tint, alphaThreshold, texture, and sampler, and set the corresponding member variables accordingly.
The setup() functions in all three classes are part of the rendering pipeline and
are called every frame before rendering an object with that material.
They set up the pipeline state and use the shader program to render the object.*/