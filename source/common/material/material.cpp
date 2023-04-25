#include "material.hpp"

#include "../asset-loader.hpp"
#include "deserialize-utils.hpp"

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
    void TintedMaterial::setup() const
    {
        // TODO: (Req 7) Write this function
        Material::setup();
        this->shader->set("tint", tint);
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
    void TexturedMaterial::setup() const
    {
        // TODO: (Req 7) Write this function
        TintedMaterial::setup();
        this->shader->set("alphaThreshold", alphaThreshold);

        if (texture)
        {
            glActiveTexture(GL_TEXTURE0);
            texture->bind();

            if (sampler)
                sampler->bind(0); // GL_TEXTURE0 is the first texture unit (don't know if this is correct or not :(

            shader->set("tex", 0);
        }

        if (t1)
        {
            glActiveTexture(GL_TEXTURE1);
            t1->bind();
            sampler->bind(1);
            shader->set("tex2", 1);
        }

        if (t2)
        {
            glActiveTexture(GL_TEXTURE2);
            t2->bind();
            sampler->bind(2);
            shader->set("tex3", 2);
        }
        
        if (t3){
            glActiveTexture(GL_TEXTURE3);
            t3->bind();
            sampler->bind(3);
            shader->set("tex4", 3);
        }
        
        if (t4){
            glActiveTexture(GL_TEXTURE4);
            t4->bind();
            sampler->bind(4);
            shader->set("tex5", 4);
        }
        
        if (t5){
            glActiveTexture(GL_TEXTURE5);
            t5->bind();
            sampler->bind(5);
            shader->set("tex6", 5);
        }
        
        if (t6){
            glActiveTexture(GL_TEXTURE6);
            t6->bind();
            sampler->bind(6);
            shader->set("tex7", 6);
        }
        
        if (t7){
            glActiveTexture(GL_TEXTURE7);
            t7->bind();
            sampler->bind(7);
            shader->set("tex8", 7);
        }
        
        if (t8){
            glActiveTexture(GL_TEXTURE8);
            t8->bind();
            sampler->bind(8);
            shader->set("tex9", 8);
        }
        
        if (t9){
            glActiveTexture(GL_TEXTURE9);
            t9->bind();
            sampler->bind(9);
            shader->set("tex10", 9);
        }
        
        if (t10){
            glActiveTexture(GL_TEXTURE10);
            t10->bind();
            sampler->bind(10);
            shader->set("tex11", 10);
        }
        
        if (t11){
            glActiveTexture(GL_TEXTURE11);
            t11->bind();
            sampler->bind(11);
            shader->set("tex12", 11);
        }
        
        if (t12){
            glActiveTexture(GL_TEXTURE12);
            t12->bind();
            sampler->bind(12);
            shader->set("tex13", 12);
        }
        
        if (t13){
            glActiveTexture(GL_TEXTURE13);
            t13->bind();
            sampler->bind(13);
            shader->set("tex14", 13);
        }
        
        if (t14){
            glActiveTexture(GL_TEXTURE14);
            t14->bind();
            sampler->bind(14);
            shader->set("tex15", 14);
        }
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

        t1 = AssetLoader<Texture2D>::get(data.value("t1", ""));
        t2 = AssetLoader<Texture2D>::get(data.value("t2", ""));
        t3 = AssetLoader<Texture2D>::get(data.value("t3", ""));
        t4 = AssetLoader<Texture2D>::get(data.value("t4", ""));
        t5 = AssetLoader<Texture2D>::get(data.value("t5", ""));
        t6 = AssetLoader<Texture2D>::get(data.value("t6", ""));
        t7 = AssetLoader<Texture2D>::get(data.value("t7", ""));
        t8 = AssetLoader<Texture2D>::get(data.value("t8", ""));
        t9 = AssetLoader<Texture2D>::get(data.value("t9", ""));
        t10 = AssetLoader<Texture2D>::get(data.value("t10", ""));
        t11 = AssetLoader<Texture2D>::get(data.value("t11", ""));
        t12 = AssetLoader<Texture2D>::get(data.value("t12", ""));
        t13 = AssetLoader<Texture2D>::get(data.value("t13", ""));
        t14 = AssetLoader<Texture2D>::get(data.value("t14", ""));
    }

}