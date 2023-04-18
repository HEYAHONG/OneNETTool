#ifndef ONENETONEJSON_H
#define ONENETONEJSON_H
#include "onenetcommon.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "inttypes.h"
#include "string.h"
#include "stdbool.h"
#include "cJSON.h"
#include "time.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//前置声明
struct OneNETOneJsonContext;


/** \brief 创建OneJson上下文
 *
 * \return struct OneNETOneJsonContext * OneJson上下文指针
 */
struct OneNETOneJsonContext *OneNETOneJsonContextNew();

/** \brief 删除OneJson上下文
 *
 * \param ctx struct OneNETOneJsonContext* OneJson上下文指针
 *
 */
void OneNETOneJsonContextDelete(struct OneNETOneJsonContext * ctx);


/** \brief OneJson上下文用户指针（用户自己管理,本库不使用）
 *
 * \param ctx struct OneNETOneJsonContext* OneJson上下文指针,不可为NULL
 * \param user_ptr void* 待设置的用户指针
 * \return void* 之前的用户指针
 *
 */
void * OneNETOneJsonUserPtr(struct OneNETOneJsonContext * ctx,void *user_ptr);

/** \brief 获取OneJson上下文用户指针
 *
 * \param ctx struct OneNETOneJsonContext* OneJson上下文指针,不可为NULL
 * \return void* 当前用户指针
 *
 */
void * OneNETOneJsonGetUserPtr(struct OneNETOneJsonContext * ctx);

/** \brief OneJson设备信息是否有效,当设备信息无效时不工作
 *
 * \param ctx struct OneNETOneJsonContext* OneJson上下文指针,不可为NULL
 * \return bool 设备信息是否有效
 *
 */
bool OneNETOneJsonDevInfoIsValid(struct OneNETOneJsonContext * ctx);

/** \brief 设置设备信息
 *
 * \param ctx struct OneNETOneJsonContext* OneJson上下文指针,不可为NULL
 * \param product_id const char* 产品ID
 * \param device_name const char* 设备名称
 *
 */
void OneNETOneJsonSetDevInfo(struct OneNETOneJsonContext * ctx,const char *product_id,const char *device_name);

typedef struct __OneNETMQTTContext
{
    /** \brief 发布MQTT消息回调函数
     *
     * \param mqttctx struct __OneNETMQTTContext* 发布MQTT消息回调函数
     * \param topic const char* 主题字符串
     * \param payload const char* 负载数据字符串
     * \return bool 是否发送成功
     *
     */
    bool (*MQTTPublish)(struct __OneNETMQTTContext * mqttctx,const char *topic,const char *payload);
    //用户指针,本库不使用
    void * user_ptr;
} OneNETMQTTContext;

/** \brief OneJson的MQTT上下文,当未设置MQTT消息上下文时不工作
 *
 * \param ctx struct OneNETOneJsonContext * OneJson上下文指针,,不可为NULL
 * \param mqttctx OneNETMQTTContext* MQTT上下文指针,可为NULL（表示仅访问当前上下文的MQTT上下文数据）
 * \return OneNETMQTTContext * 当前OneJson上下文的MQTT上下文指针,当ctx参数为NULL时值为NULL
 *
 */
OneNETMQTTContext * OneNETOneJsonMQTTContext(struct OneNETOneJsonContext * ctx,OneNETMQTTContext * mqttctx);

/** \brief 向OneJson上下文输入MQTT消息
 *
 * \param ctx struct OneNETOneJsonContext* OneJson上下文指针,不可为NULL
 * \param topic const char* 主题字符串,不可为NULL
 * \param payload const char* 负载数据字符串,不可为NULL,注意:必须确保输入为字符串
 * \return bool 是否成功处理
 *
 */
bool OneNETOneJsonInputMQTTMessage(struct OneNETOneJsonContext * ctx,const char *topic,const char *payload);

/** \brief OneJson中的id值
 *
 * \param ctx struct OneNETOneJsonContext* OneJson上下文指针,不可为NULL
 * \param id uint64_t* 待设置的id值.为NULL表示仅查看
 * \return uint64_t 当前id值,当ctx为空时永远返回0
 *
 */
uint64_t OneNETOneJsonIdNumber(struct OneNETOneJsonContext * ctx,uint64_t *id);

/** \brief 获取OneJson的id值并自增
 *
 * \param ctx struct OneNETOneJsonContext* OneJson上下文指针,不可为NULL
 * \return uint64_t 当前id值,当ctx为空时永远返回0
 *
 */
uint64_t OneNETOneJsonIdNumberAndIncrease(struct OneNETOneJsonContext * ctx);

/********************************************************************************************
OneJson设备属性/事件接口
********************************************************************************************/

typedef struct
{
    //属性名称,通常不可为空
    const char *key;
    //属性值,通常不可为空,其类型可以为cJSON支持的任意类型（除了Null）
    cJSON *value;
} OneNETOneJsonPropertyParam;

/** \brief 申请OneNETOneJsonPropertyParam
 *
 * \param __key  属性名称
 * \param __type 可为String,Number,Bool,ObjectReference(对象引用,原cJSON*不受影响),ArrayReference(数组引用,原cJSON*不受影响)
 * \param __value 值,根据type的不同可为String(const char *),Number(double/int),Bool(true/false),ObjectReference(cJSON*),ArrayReference(cJSNO*)
 * \return 返回OneNETOneJsonPropertyParam,注意：并非指针。
 *
 */
#define OneNETOneJsonPropertyParamNew(__key,__type,__value) \
                                                    ({ \
                                                    OneNETOneJsonPropertyParam ret = {0};\
                                                    ret.key = (const char *)OneNETStrdup(__key);\
                                                    ret.value = cJSON_Create##__type(__value);\
                                                    ret;\
                                                    })
//辅助申请OneNETOneJsonPropertyParam的函数,可申请String,Number,Bool,ObjectReference,ArrayReference。
#define OneNETOneJsonPropertyParamNewString(key,value) OneNETOneJsonPropertyParamNew(key,String,value)
#define OneNETOneJsonPropertyParamNewNumber(key,value) OneNETOneJsonPropertyParamNew(key,Number,value)
#define OneNETOneJsonPropertyParamNewBool(key,value) OneNETOneJsonPropertyParamNew(key,Bool,value)
#define OneNETOneJsonPropertyParamNewObjectReference(key,value) OneNETOneJsonPropertyParamNew(key,ObjectReference,value)
#define OneNETOneJsonPropertyParamNewArrayReference(key,value) OneNETOneJsonPropertyParamNew(key,ArrayReference,value)


/** \brief 释放由OneNETOneJsonPropertyParamNew申请的结构体,注意:不可用于用户自己管理的OneNETOneJsonPropertyParam。
 *
 * \param Param 待释放的OneNETOneJsonPropertyParam,仅释放key与value,注意:并非指针
 *
 */
#define OneNETOneJsonPropertyParamDelete(Param) \
                                                {\
                                                if(Param.key!=NULL)\
                                                    OneNETFree((void*)Param.key);\
                                                if(Param.value!=NULL)\
                                                    cJSON_Delete(Param.value);\
                                                }


typedef struct
{
    //属性值
    OneNETOneJsonPropertyParam param;
    //属性生成时间戳
    time_t time_stamp;
} OneNETOneJsonPropertyPostParam;

/** \brief OneJson属性上报
 *
 * \param ctx struct OneNETOneJsonContext* OneJson上下文指针,不可为NULL
 * \param params[] OneNETOneJsonPropertyPostParam 属性上报参数数组起始地址,注意:属性上报参数中的指针由用户管理(用户自行创建与删除)
 * \param params_length size_t 属性上报参数数组长度
 * \param id uint64_t 消息id
 * \return bool 是否发送成功
 *
 */
bool OneNETOneJsonPropertyPost(struct OneNETOneJsonContext * ctx,OneNETOneJsonPropertyPostParam params[],size_t params_length,uint64_t id);

typedef struct __OneNETOneJsonPropertyPostReplyCallback
{
    /** \brief 属性上报回调函数函数
     *
     * \param ctx struct __OneNETOneJsonPropertyPostReplyCallback* 属性上报回调函数函数
     * \param id uint64_t OneJson的id
     * \param code int OneJson的返回代码。200表示成功
     * \param msg const char* OneJson的消息
     *
     */
    void (*OnPropertyPostReply)(struct __OneNETOneJsonPropertyPostReplyCallback *ctx,uint64_t id,int code,const char *msg);
    //用户指针,本库不使用
    void *user_ptr;
} OneNETOneJsonPropertyPostReplyCallback;

/** \brief OneJson属性上报回调函数
 *
 * \param ctx struct OneNETOneJsonContext* OneJson上下文指针,不可为NULL
 * \param callback OneNETOneJsonPropertyPostReplyCallback* 待设置的OneJson属性上报回调函数指针,可为NULL(表示仅访问当前上下文的OneJson属性上报回调函数)
 * \return OneNETOneJsonPropertyPostReplyCallback* OneJson属性上报回调函数指针
 *
 */
OneNETOneJsonPropertyPostReplyCallback * OneNETOneJsonOnPropertyPostReplyCallback(struct OneNETOneJsonContext * ctx,OneNETOneJsonPropertyPostReplyCallback * callback);

typedef struct __OneNETOneJsonPropertySetCallback
{
    /** \brief 属性设置回调函数
     *
     * \param ctx struct __OneNETOneJsonPropertySetCallback* 属性设置回调函数上下文
     * \param key const char* 属性名称
     * \param value cJSON* 属性值,可以为任意json支持的类型
     * \return bool 是否设置成功。当有一个属性设置失败时,将不会给平台发送消息
     *
     */
    bool (*OnPropertySet)(struct __OneNETOneJsonPropertySetCallback *ctx,const char *key,cJSON *value);
    //用户指针,本库不使用
    void *user_ptr;
} OneNETOneJsonPropertySetCallback;

/** \brief OneJson属性设置回调函数
 *
 * \param ctx struct OneNETOneJsonContext* OneJson上下文指针,不可为NULL
 * \param callback OneNETOneJsonPropertySetCallback* 待设置的OneJson属性设置回调函数指针,可为NULL(表示仅访问当前上下文的OneJson属性设置回调函数)
 * \return OneNETOneJsonPropertySetCallback* OneJson属性设置回调函数指针
 *
 */
OneNETOneJsonPropertySetCallback * OneNETOneJsonOnPropertySetCallback(struct OneNETOneJsonContext * ctx,OneNETOneJsonPropertySetCallback *callback);

typedef struct __OneNETOneJsonPropertyGetCallback
{

    /** \brief 属性获取回调函数
     *
     * \param ctx struct __OneNETOneJsonPropertyGetCallback* 属性获取函数上下文
     * \param key const char* 属性名称
     * \param value cJSON** 属性值,用户需要通过此函数传出一个cJSON *作为返回
     * \return bool 是否获取成功,当失败时不会调用OnPropertyGetEnd。
     *
     */
    bool (*OnPropertyGet)(struct __OneNETOneJsonPropertyGetCallback *ctx,const char *key,cJSON **value);
    /** \brief 属性获取结束函数,当属性获取结束时调用此函数,此函数主要用于清理OnPropertyGet申请的资源(如OnPropertyGet传出的cJSON*值)
     *
     * \param ctx struct __OneNETOneJsonPropertyGetCallback* 属性获取结束函数
     * \param key const char* 属性名称
     * \param value cJSON** 属性值,指向OnPropertyGet传出的参数
     * \return bool 是否成功
     *
     */
    bool (*OnPropertyGetEnd)(struct __OneNETOneJsonPropertyGetCallback *ctx,const char *key,cJSON **value);
    //用户指针,本库不使用
    void *user_ptr;
} OneNETOneJsonPropertyGetCallback;

/** \brief OneJson属性获取回调函数
 *
 * \param ctx struct OneNETOneJsonContext* OneJson上下文指针,不可为NULL
 * \param callback OneNETOneJsonPropertyGetCallback* 待设置的OneJson属性获取回调函数指针,可为NULL(表示仅访问当前上下文的OneJson属性获取回调函数)
 * \return OneNETOneJsonPropertyGetCallback* OneJson属性获取回调函数指针
 *
 */
OneNETOneJsonPropertyGetCallback * OneNETOneJsonOnPropertyGetCallback(struct OneNETOneJsonContext * ctx,OneNETOneJsonPropertyGetCallback *callback);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ONENETONEJSON_H
