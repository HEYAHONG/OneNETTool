#include "onenetcommon.h"
#include "onenetonejson.h"

struct OneNETOneJsonContext
{
    //产品ID
    char * product_id;
    //设备ID
    char * device_name;
    //MQTT上下文
    OneNETMQTTContext mqtt_context;
    //当前id
    uint64_t id;
    //用户指针
    void *user_ptr;
    //属性上报回复回调
    OneNETOneJsonPropertyPostReplyCallback on_property_post_reply_callback;
    //属性设置回调函数
    OneNETOneJsonPropertySetCallback on_property_set_callback;
    //属性获取回调函数
    OneNETOneJsonPropertyGetCallback on_property_get_callback;
};


struct OneNETOneJsonContext *OneNETOneJsonContextNew()
{
    //确保Common初始化
    OneNETCommonInit();

    struct OneNETOneJsonContext * ctx=OneNETMalloc(sizeof(struct OneNETOneJsonContext));
    if(ctx!=NULL)
    {
        memset(ctx,0,sizeof(struct OneNETOneJsonContext));
    }
    return ctx;
}

void OneNETOneJsonContextDelete(struct OneNETOneJsonContext * ctx)
{
    if(ctx!=NULL)
    {
        if(ctx->product_id!=NULL)
        {
            OneNETFree(ctx->product_id);
        }
        if(ctx->device_name!=NULL)
        {
            OneNETFree(ctx->device_name);
        }
        //释放上下文
        OneNETFree(ctx);
    }
}

void * OneNETOneJsonUserPtr(struct OneNETOneJsonContext * ctx,void *user_ptr)
{
    if(ctx!=NULL)
    {
        void *orig_ctx=ctx->user_ptr;
        ctx->user_ptr=user_ptr;
        return orig_ctx;
    }
    return NULL;
}

void * OneNETOneJsonGetUserPtr(struct OneNETOneJsonContext * ctx)
{
    if(ctx!=NULL)
    {
        return ctx->user_ptr;
    }
    return NULL;
}

bool OneNETOneJsonDevInfoIsValid(struct OneNETOneJsonContext * ctx)
{
    if(ctx==NULL)
    {
        return false;
    }
    return ctx->product_id!=NULL && ctx->device_name!=NULL;
}

void OneNETOneJsonSetDevInfo(struct OneNETOneJsonContext * ctx,const char *product_id,const char *device_name)
{
    if(ctx!=NULL)
    {
        if(product_id!=NULL)
        {
            if(ctx->product_id!=NULL)
            {
                OneNETFree(ctx->product_id);
            }
            ctx->product_id=OneNETStrdup(product_id);
        }
        if(device_name!=NULL)
        {
            if(ctx->device_name!=NULL)
            {
                OneNETFree(ctx->device_name);
            }
            ctx->device_name=OneNETStrdup(device_name);
        }
    }
}

OneNETMQTTContext * OneNETOneJsonMQTTContext(struct OneNETOneJsonContext * ctx,OneNETMQTTContext * mqttctx)
{
    if(ctx!=NULL)
    {
        if(mqttctx!=NULL)
        {
            ctx->mqtt_context=(*mqttctx);
        }
        return &ctx->mqtt_context;
    }

    return NULL;
}

bool OneNETOneJsonInputMQTTMessage(struct OneNETOneJsonContext * ctx,const char *topic,const char *payload)
{
    //检查参数
    if(ctx==NULL || topic == NULL || payload ==NULL )
    {
        return false;
    }

    bool ret=false;

    char * plies_store=OneNETStrdup(topic);
    const char * plies[10]= {0};
    size_t plies_size=0;
    {
        //对MQTT主题进行分析(分层)
        size_t plies_store_length=strlen(plies_store);
        const char *ply_start=plies_store;
        size_t ply_count=0;
        for(size_t i=0; i<plies_store_length; i++)
        {
            if(plies_store[i]=='/')
            {
                plies_store[i]='\0';
                plies[ply_count]=ply_start;
                ply_count++;
                ply_start=&plies_store[i+1];
            }

            if((sizeof(plies)/sizeof(plies[0])-1) >= ply_count)
            {
                //层数过多
                break;
            }
        }
        if(strlen(ply_start)!=0)
        {
            plies[ply_count]=ply_start;
            ply_count++;
        }
        plies_size=ply_count;
    }

    {
        //检查是否是OneNET物联网消息
        if(plies_size < 4)
        {
            //层数太低
            goto clean_plies;
        }

        if(!OneNETStringIsSame(plies[0],"$sys"))
        {
            goto clean_plies;
        }

        if(!OneNETStringIsSame(plies[1],ctx->product_id))
        {
            //产品id不符合
            goto clean_plies;
        }

        if(!OneNETStringIsSame(plies[2],ctx->device_name))
        {
            //设备名称不符合
            goto clean_plies;
        }

        if(!OneNETStringIsSame(plies[3],"thing"))
        {
            goto clean_plies;
        }
    }


    cJSON *reqjson=cJSON_Parse(payload);
    if(reqjson==NULL)
    {
        goto clean_plies;
    }

    if(plies_size >= 5 && OneNETStringIsSame(plies[4],"property"))
    {
        //属性数据

        if(plies_size == 7 && OneNETStringIsSame(plies[5],"post") && OneNETStringIsSame(plies[6],"reply"))
        {
            //属性上报回复
            cJSON *cjson_id=cJSON_GetObjectItem(reqjson,"id");
            cJSON *cjson_code=cJSON_GetObjectItem(reqjson,"code");
            cJSON *cjson_msg=cJSON_GetObjectItem(reqjson,"msg");
            if(cJSON_IsString(cjson_id) && cJSON_IsNumber(cjson_code) && cJSON_IsString(cjson_msg))
            {
                uint64_t id=0;
                sscanf(cJSON_GetStringValue(cjson_id), "%" PRIu64,&id);
                //回复的参数正确
                if(ctx->on_property_post_reply_callback.OnPropertyPostReply!=NULL)
                {
                    ctx->on_property_post_reply_callback.OnPropertyPostReply(&ctx->on_property_post_reply_callback,id,cJSON_GetNumberValue(cjson_code),cJSON_GetStringValue(cjson_msg));
                    ret=true;
                }
            }
        }

        if(plies_size == 6 && OneNETStringIsSame(plies[5],"set"))
        {
            //设置属性
            if(ctx->on_property_set_callback.OnPropertySet==NULL)
            {
                goto clean_reqjson;
            }

            cJSON *cjson_params=cJSON_GetObjectItem(reqjson,"params");

            bool isallok=true;
            if(cJSON_IsObject(cjson_params))
            {
                for(int i=0; i<cJSON_GetArraySize(cjson_params); i++)
                {
                    cJSON *cjson_param=cJSON_GetArrayItem(cjson_params,i);
                    if(!ctx->on_property_set_callback.OnPropertySet(&ctx->on_property_set_callback,cjson_param->string,cjson_param))
                    {
                        isallok=false;
                    }
                }
            }

            cJSON * cjson_id=cJSON_GetObjectItem(reqjson,"id");
            if(isallok && cJSON_IsString(cjson_id))
            {
                //返回MQTT消息(仅成功返回)
                cJSON * cjson_reply=cJSON_CreateObject();
                if(cjson_reply!=NULL)
                {
                    cJSON_AddStringToObject(cjson_reply,"id",cJSON_GetStringValue(cjson_id));
                    cJSON_AddNumberToObject(cjson_reply,"code",200);
                    cJSON_AddStringToObject(cjson_reply,"msg","ok");
                    {
                        size_t topic_length=50+strlen(ctx->product_id)+strlen(ctx->device_name);
                        char * topic=(char *)OneNETMalloc(topic_length);
                        if(topic!=NULL)
                        {
                            memset(topic,0,topic_length);
                            snprintf(topic,topic_length,"$sys/%s/%s/thing/property/set_reply",ctx->product_id,ctx->device_name);
                            char * payload=(char *)cJSON_Print(cjson_reply);
                            if(payload!=NULL)
                            {
                                if(ctx->mqtt_context.MQTTPublish!=NULL)
                                {
                                    ret=ctx->mqtt_context.MQTTPublish(&ctx->mqtt_context,topic,payload);
                                }
                                OneNETFree(topic);
                                cJSON_free(payload);
                            }
                            else
                            {
                                OneNETFree(topic);
                            }

                        }
                    }
                    cJSON_Delete(cjson_reply);
                }
            }
        }

        if(plies_size == 6 && OneNETStringIsSame(plies[5],"get"))
        {
            //获取属性
            if(ctx->on_property_get_callback.OnPropertyGet==NULL)
            {
                goto clean_reqjson;
            }

            cJSON *cjson_params=cJSON_GetObjectItem(reqjson,"params");


            cJSON * cjson_id=cJSON_GetObjectItem(reqjson,"id");
            if(cJSON_IsString(cjson_id))
            {
                //返回MQTT消息(仅成功返回)
                cJSON * cjson_reply=cJSON_CreateObject();
                if(cjson_reply!=NULL)
                {
                    cJSON_AddStringToObject(cjson_reply,"id",cJSON_GetStringValue(cjson_id));
                    cJSON_AddNumberToObject(cjson_reply,"code",200);
                    cJSON_AddStringToObject(cjson_reply,"msg","ok");
                    {
                        //读取属性
                        if(cJSON_IsObject(cjson_params))
                        {
                            cJSON *cjson_data=cJSON_AddObjectToObject(cjson_reply,"data");
                            for(int i=0; i<cJSON_GetArraySize(cjson_params); i++)
                            {
                                cJSON *cjson_param=cJSON_GetArrayItem(cjson_params,i);
                                if(cJSON_IsString(cjson_param))
                                {
                                    cJSON *datavalue=NULL;
                                    if(ctx->on_property_get_callback.OnPropertyGet(&ctx->on_property_get_callback,cJSON_GetStringValue(cjson_param),&datavalue))
                                    {
                                        if(datavalue!=NULL)
                                        {
                                            cJSON_AddItemToObject(cjson_data,cJSON_GetStringValue(cjson_param),cJSON_Duplicate(datavalue,true));
                                        }
                                        if(ctx->on_property_get_callback.OnPropertyGetEnd!=NULL)
                                        {
                                            ctx->on_property_get_callback.OnPropertyGetEnd(&ctx->on_property_get_callback,cJSON_GetStringValue(cjson_param),&datavalue);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    {
                        size_t topic_length=50+strlen(ctx->product_id)+strlen(ctx->device_name);
                        char * topic=(char *)OneNETMalloc(topic_length);
                        if(topic!=NULL)
                        {
                            memset(topic,0,topic_length);
                            snprintf(topic,topic_length,"$sys/%s/%s/thing/property/get_reply",ctx->product_id,ctx->device_name);
                            char * payload=(char *)cJSON_Print(cjson_reply);
                            if(payload!=NULL)
                            {
                                if(ctx->mqtt_context.MQTTPublish!=NULL)
                                {
                                    ret=ctx->mqtt_context.MQTTPublish(&ctx->mqtt_context,topic,payload);
                                }
                                OneNETFree(topic);
                                cJSON_free(payload);
                            }
                            else
                            {
                                OneNETFree(topic);
                            }

                        }
                    }
                    cJSON_Delete(cjson_reply);
                }
            }
        }


    }


clean_reqjson:
    if(reqjson!=NULL)
    {
        cJSON_Delete(reqjson);
    }
clean_plies:
    if(plies_store!=NULL)
    {
        OneNETFree(plies_store);
    }

    return ret;
}

uint64_t OneNETOneJsonIdNumber(struct OneNETOneJsonContext * ctx,uint64_t *id)
{
    if(ctx!=NULL)
    {
        if(id!=NULL)
        {
            ctx->id=(*id);
        }
        return ctx->id;
    }
    return 0;
}

uint64_t OneNETOneJsonIdNumberAndIncrease(struct OneNETOneJsonContext * ctx)
{
    if(ctx!=NULL)
    {
        return ctx->id++;
    }
    return 0;
}

bool OneNETOneJsonPropertyPost(struct OneNETOneJsonContext * ctx,OneNETOneJsonPropertyPostParam params[],size_t params_length,uint64_t id)
{
    if(ctx == NULL || params == NULL || params_length == 0)
    {
        return false;
    }

    if(ctx->mqtt_context.MQTTPublish==NULL)
    {
        return false;
    }

    if(ctx->product_id==NULL || ctx->device_name ==NULL)
    {
        return false;
    }

    bool ret=false;

    cJSON *cjson=cJSON_CreateObject();
    if(cjson==NULL)
    {
        goto clean_cjson;
    }

    //添加version
    cJSON_AddStringToObject(cjson,"version","1.0");

    {
        //添加id(13位数字)
        char buff[32]= {0};
        const char *id_str=buff;
        snprintf(buff,sizeof(buff)-1, "%" PRIu64,id);
        if(strlen(buff)>13)
        {
            id_str=&buff[strlen(buff)-13];
        }
        cJSON_AddStringToObject(cjson,"id",id_str);
    }

    {
        cJSON *cjson_params=cJSON_AddObjectToObject(cjson,"params");
        for(size_t i=0; i<params_length; i++)
        {
            OneNETOneJsonPropertyPostParam *param=&params[i];
            if(param->param.key==NULL || param->param.value==NULL)
            {
                continue;
            }
            cJSON * cjson_params_param=cJSON_AddObjectToObject(cjson_params,param->param.key);
            cJSON_AddNumberToObject(cjson_params_param,"time",param->time_stamp);
            cJSON_AddItemToObject(cjson_params_param,"value",cJSON_Duplicate(param->param.value,true));
        }
    }

    {
        //发送MQTT消息
        size_t topic_length=50+strlen(ctx->product_id)+strlen(ctx->device_name);
        char * topic=(char *)OneNETMalloc(topic_length);
        if(topic==NULL)
        {
            goto clean_cjson;
        }
        memset(topic,0,topic_length);
        snprintf(topic,topic_length,"$sys/%s/%s/thing/property/post",ctx->product_id,ctx->device_name);
        char * payload=(char *)cJSON_Print(cjson);
        if(payload==NULL)
        {
            OneNETFree(topic);
            goto clean_cjson;
        }
        ret=ctx->mqtt_context.MQTTPublish(&ctx->mqtt_context,topic,payload);
        OneNETFree(topic);
        cJSON_free(payload);
    }

clean_cjson:
    if(cjson!=NULL)
    {
        cJSON_Delete(cjson);
    }
    return ret;
}

OneNETOneJsonPropertyPostReplyCallback * OneNETOneJsonOnPropertyPostReplyCallback(struct OneNETOneJsonContext * ctx,OneNETOneJsonPropertyPostReplyCallback * callback)
{
    if(ctx!=NULL)
    {
        if(callback!=NULL)
        {
            ctx->on_property_post_reply_callback=(*callback);
        }
        return &ctx->on_property_post_reply_callback;
    }
    return NULL;
}

OneNETOneJsonPropertySetCallback * OneNETOneJsonOnPropertySetCallback(struct OneNETOneJsonContext * ctx,OneNETOneJsonPropertySetCallback *callback)
{
    if(ctx!=NULL)
    {
        if(callback!=NULL)
        {
            ctx->on_property_set_callback=(*callback);
        }
        return &ctx->on_property_set_callback;
    }
    return NULL;
}

OneNETOneJsonPropertyGetCallback * OneNETOneJsonOnPropertyGetCallback(struct OneNETOneJsonContext * ctx,OneNETOneJsonPropertyGetCallback *callback)
{
    if(ctx!=NULL)
    {
        if(callback!=NULL)
        {
            ctx->on_property_get_callback=(*callback);
        }
        return &ctx->on_property_get_callback;
    }
    return NULL;
}
