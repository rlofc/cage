LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := CAGE

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
     ../SDL2_mixer/ \
     ../SDL2_image/

LOCAL_SRC_FILES := src/animate.c \
                   src/cage.c \
                   src/easing.c \
                   src/font.c \
                   src/geometry.c \
                   src/image.c \
                   src/keyboard.c \
                   src/mouse.c \
                   src/screen.c \
                   src/sound.c \
                   src/sprite.c \
                   src/timeline.c
	

LOCAL_LDLIBS :=
LOCAL_STATIC_LIBRARIES :=
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer

LOCAL_EXPORT_C_INCLUDES += $(LOCAL_C_INCLUDES)

include $(BUILD_SHARED_LIBRARY)
