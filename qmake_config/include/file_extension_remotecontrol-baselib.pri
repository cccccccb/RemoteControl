SOURCE_BASE_HEADERS +=                                                      \
    $${_PRO_FILE_PWD_}/applications_reader.h                                \
    $${_PRO_FILE_PWD_}/base64.h                                             \
    $${_PRO_FILE_PWD_}/bitset.h                                             \
    $${_PRO_FILE_PWD_}/command_line.h                                       \
    $${_PRO_FILE_PWD_}/compiler_specific.h                                  \
    $${_PRO_FILE_PWD_}/converter.h                                          \
    $${_PRO_FILE_PWD_}/cpuid_util.h                                         \
    $${_PRO_FILE_PWD_}/crc32.h                                              \
    $${_PRO_FILE_PWD_}/debug.h                                              \
    $${_PRO_FILE_PWD_}/edid.h                                               \
    $${_PRO_FILE_PWD_}/endian_util.h                                        \
    $${_PRO_FILE_PWD_}/environment.h                                        \
    $${_PRO_FILE_PWD_}/guid.h                                               \
    $${_PRO_FILE_PWD_}/license_reader.h                                     \
    $${_PRO_FILE_PWD_}/location.h                                           \
    $${_PRO_FILE_PWD_}/logging.h                                            \
    $${_PRO_FILE_PWD_}/macros_magic.h                                       \
    $${_PRO_FILE_PWD_}/power_controller.h                                   \
    $${_PRO_FILE_PWD_}/process_handle.h                                     \
    $${_PRO_FILE_PWD_}/scoped_clear_last_error.h                            \
    $${_PRO_FILE_PWD_}/scoped_task_runner.h                                 \
    $${_PRO_FILE_PWD_}/scoped_logging.h                                     \
    $${_PRO_FILE_PWD_}/service.h                                            \
    $${_PRO_FILE_PWD_}/session_id.h                                         \
    $${_PRO_FILE_PWD_}/smbios.h                                             \
    $${_PRO_FILE_PWD_}/smbios_parser.h                                      \
    $${_PRO_FILE_PWD_}/smbios_reader.h                                      \
    $${_PRO_FILE_PWD_}/stl_util.h                                           \
    $${_PRO_FILE_PWD_}/sys_info.h                                           \
    $${_PRO_FILE_PWD_}/system_error.h                                       \
    $${_PRO_FILE_PWD_}/system_time.h                                        \
    $${_PRO_FILE_PWD_}/task_runner.h                                        \
    $${_PRO_FILE_PWD_}/version.h                                            \
    $${_PRO_FILE_PWD_}/waitable_event.h                                     \
    $${_PRO_FILE_PWD_}/waitable_timer.h                                     \
    $${_PRO_FILE_PWD_}/optional.hpp                                         \
    $${_PRO_FILE_PWD_}/filesystem.hpp                                       \
    $${_PRO_FILE_PWD_}/win/battery_enumerator.h                             \
    $${_PRO_FILE_PWD_}/win/desktop.h                                        \
    $${_PRO_FILE_PWD_}/win/device.h                                         \
    $${_PRO_FILE_PWD_}/win/device_enumerator.h                              \
    $${_PRO_FILE_PWD_}/win/drive_enumerator.h                               \
    $${_PRO_FILE_PWD_}/win/event_enumerator.h                               \
    $${_PRO_FILE_PWD_}/win/file_version_info.h                              \
    $${_PRO_FILE_PWD_}/win/message_window.h                                 \
    $${_PRO_FILE_PWD_}/win/mini_dump_writer.h                               \
    $${_PRO_FILE_PWD_}/win/monitor_enumerator.h                             \
    $${_PRO_FILE_PWD_}/win/net_share_enumerator.h                           \
    $${_PRO_FILE_PWD_}/win/object_watcher.h                                 \
    $${_PRO_FILE_PWD_}/win/power_info.h                                     \
    $${_PRO_FILE_PWD_}/win/printer_enumerator.h                             \
    $${_PRO_FILE_PWD_}/win/process.h                                        \
    $${_PRO_FILE_PWD_}/win/process_util.h                                   \
    $${_PRO_FILE_PWD_}/win/registry.h                                       \
    $${_PRO_FILE_PWD_}/win/resource_util.h                                  \
    $${_PRO_FILE_PWD_}/win/safe_mode_util.h                                 \
    $${_PRO_FILE_PWD_}/win/scoped_clipboard.h                               \
    $${_PRO_FILE_PWD_}/win/scoped_co_mem.h                                  \
    $${_PRO_FILE_PWD_}/win/scoped_com_initializer.h                         \
    $${_PRO_FILE_PWD_}/win/scoped_device_info.h                             \
    $${_PRO_FILE_PWD_}/win/scoped_gdi_object.h                              \
    $${_PRO_FILE_PWD_}/win/scoped_hdc.h                                     \
    $${_PRO_FILE_PWD_}/win/scoped_hglobal.h                                 \
    $${_PRO_FILE_PWD_}/win/scoped_impersonator.h                            \
    $${_PRO_FILE_PWD_}/win/scoped_local.h                                   \
    $${_PRO_FILE_PWD_}/win/scoped_object.h                                  \
    $${_PRO_FILE_PWD_}/win/scoped_select_object.h                           \
    $${_PRO_FILE_PWD_}/win/scoped_thread_desktop.h                          \
    $${_PRO_FILE_PWD_}/win/scoped_user_object.h                             \
    $${_PRO_FILE_PWD_}/win/scoped_wts_memory.h                              \
    $${_PRO_FILE_PWD_}/win/security_helpers.h                               \
    $${_PRO_FILE_PWD_}/win/service_controller.h                             \
    $${_PRO_FILE_PWD_}/win/service_enumerator.h                             \
    $${_PRO_FILE_PWD_}/win/session_enumerator.h                             \
    $${_PRO_FILE_PWD_}/win/session_info.h                                   \
    $${_PRO_FILE_PWD_}/win/session_status.h                                 \
    $${_PRO_FILE_PWD_}/win/session_watcher.h                                \
    $${_PRO_FILE_PWD_}/win/user_enumerator.h                                \
    $${_PRO_FILE_PWD_}/win/user_group_enumerator.h                          \
    $${_PRO_FILE_PWD_}/win/video_adapter_enumerator.h                       \
    $${_PRO_FILE_PWD_}/win/windows_version.h                                \
    $${_PRO_FILE_PWD_}/base_export.h

SOURCE_BASE_SOURCES +=                                                      \
    $${_PRO_FILE_PWD_}/base64.cc                                            \
    $${_PRO_FILE_PWD_}/command_line.cc                                      \
    $${_PRO_FILE_PWD_}/cpuid_util.cc                                        \
    $${_PRO_FILE_PWD_}/crc32.cc                                             \
    $${_PRO_FILE_PWD_}/debug.cc                                             \
    $${_PRO_FILE_PWD_}/edid.cc                                              \
    $${_PRO_FILE_PWD_}/endian_util.cc                                       \
    $${_PRO_FILE_PWD_}/environment.cc                                       \
    $${_PRO_FILE_PWD_}/guid.cc                                              \
    $${_PRO_FILE_PWD_}/location.cc                                          \
    $${_PRO_FILE_PWD_}/logging.cc                                           \
    $${_PRO_FILE_PWD_}/process_handle.cc                                    \
    $${_PRO_FILE_PWD_}/scoped_clear_last_error.cc                           \
    $${_PRO_FILE_PWD_}/scoped_task_runner.cc                                \
    $${_PRO_FILE_PWD_}/scoped_logging.cc                                    \
    $${_PRO_FILE_PWD_}/session_id.cc                                        \
    $${_PRO_FILE_PWD_}/smbios_parser.cc                                     \
    $${_PRO_FILE_PWD_}/sys_info.cc                                          \
    $${_PRO_FILE_PWD_}/system_error.cc                                      \
    $${_PRO_FILE_PWD_}/system_time.cc                                       \
    $${_PRO_FILE_PWD_}/task_runner.cc                                       \
    $${_PRO_FILE_PWD_}/version.cc                                           \
    $${_PRO_FILE_PWD_}/waitable_event.cc                                    \
    $${_PRO_FILE_PWD_}/waitable_timer.cc                                    \
    $${_PRO_FILE_PWD_}/applications_reader_win.cc                           \
    $${_PRO_FILE_PWD_}/license_reader_win.cc                                \
    $${_PRO_FILE_PWD_}/power_controller_win.cc                              \
    $${_PRO_FILE_PWD_}/smbios_reader_win.cc                                 \
    $${_PRO_FILE_PWD_}/service_win.cc                                       \
    $${_PRO_FILE_PWD_}/sys_info_win.cc                                      \
    $${_PRO_FILE_PWD_}/win/battery_enumerator.cc                            \
    $${_PRO_FILE_PWD_}/win/desktop.cc                                       \
    $${_PRO_FILE_PWD_}/win/device.cc                                        \
    $${_PRO_FILE_PWD_}/win/device_enumerator.cc                             \
    $${_PRO_FILE_PWD_}/win/drive_enumerator.cc                              \
    $${_PRO_FILE_PWD_}/win/event_enumerator.cc                              \
    $${_PRO_FILE_PWD_}/win/file_version_info.cc                             \
    $${_PRO_FILE_PWD_}/win/message_window.cc                                \
    $${_PRO_FILE_PWD_}/win/mini_dump_writer.cc                              \
    $${_PRO_FILE_PWD_}/win/monitor_enumerator.cc                            \
    $${_PRO_FILE_PWD_}/win/net_share_enumerator.cc                          \
    $${_PRO_FILE_PWD_}/win/object_watcher.cc                                \
    $${_PRO_FILE_PWD_}/win/power_info.cc                                    \
    $${_PRO_FILE_PWD_}/win/printer_enumerator.cc                            \
    $${_PRO_FILE_PWD_}/win/process.cc                                       \
    $${_PRO_FILE_PWD_}/win/process_util.cc                                  \
    $${_PRO_FILE_PWD_}/win/registry.cc                                      \
    $${_PRO_FILE_PWD_}/win/resource_util.cc                                 \
    $${_PRO_FILE_PWD_}/win/safe_mode_util.cc                                \
    $${_PRO_FILE_PWD_}/win/scoped_clipboard.cc                              \
    $${_PRO_FILE_PWD_}/win/scoped_com_initializer.cc                        \
    $${_PRO_FILE_PWD_}/win/scoped_impersonator.cc                           \
    $${_PRO_FILE_PWD_}/win/scoped_thread_desktop.cc                         \
    $${_PRO_FILE_PWD_}/win/service_controller.cc                            \
    $${_PRO_FILE_PWD_}/win/security_helpers.cc                              \
    $${_PRO_FILE_PWD_}/win/service_enumerator.cc                            \
    $${_PRO_FILE_PWD_}/win/session_enumerator.cc                            \
    $${_PRO_FILE_PWD_}/win/session_info.cc                                  \
    $${_PRO_FILE_PWD_}/win/session_status.cc                                \
    $${_PRO_FILE_PWD_}/win/session_watcher.cc                               \
    $${_PRO_FILE_PWD_}/win/user_enumerator.cc                               \
    $${_PRO_FILE_PWD_}/win/user_group_enumerator.cc                         \
    $${_PRO_FILE_PWD_}/win/video_adapter_enumerator.cc                      \
    $${_PRO_FILE_PWD_}/win/windows_version.cc                               \

SOURCE_BASE_AUDIO_HEADERS +=                                                \
    $${_PRO_FILE_PWD_}/audio/audio_capturer.h                               \
    $${_PRO_FILE_PWD_}/audio/audio_capturer_wrapper.h                       \
    $${_PRO_FILE_PWD_}/audio/audio_output.h                                 \
    $${_PRO_FILE_PWD_}/audio/audio_player.h                                 \
    $${_PRO_FILE_PWD_}/audio/audio_silence_detector.h                       \
    $${_PRO_FILE_PWD_}/audio/audio_volume_filter.h                          \
    $${_PRO_FILE_PWD_}/audio/audio_capturer_win.h                           \
    $${_PRO_FILE_PWD_}/audio/audio_output_win.h                             \
    $${_PRO_FILE_PWD_}/audio/audio_volume_filter_win.h                      \
    $${_PRO_FILE_PWD_}/audio/win/audio_util_win.h                           \
    $${_PRO_FILE_PWD_}/audio/win/default_audio_device_change_detector.h     \
    $${_PRO_FILE_PWD_}/audio/win/scoped_mmcss_registration.h                \

SOURCE_BASE_AUDIO_SOURCES +=                                                \
    $${_PRO_FILE_PWD_}/audio/audio_capturer.cc                              \
    $${_PRO_FILE_PWD_}/audio/audio_capturer_wrapper.cc                      \
    $${_PRO_FILE_PWD_}/audio/audio_output.cc                                \
    $${_PRO_FILE_PWD_}/audio/audio_player.cc                                \
    $${_PRO_FILE_PWD_}/audio/audio_silence_detector.cc                      \
    $${_PRO_FILE_PWD_}/audio/audio_volume_filter.cc                         \
    $${_PRO_FILE_PWD_}/audio/audio_capturer_win.cc                          \
    $${_PRO_FILE_PWD_}/audio/audio_output_win.cc                            \
    $${_PRO_FILE_PWD_}/audio/audio_volume_filter_win.cc                     \
    $${_PRO_FILE_PWD_}/audio/win/audio_util_win.cc                          \
    $${_PRO_FILE_PWD_}/audio/win/default_audio_device_change_detector.cc    \
    $${_PRO_FILE_PWD_}/audio/win/scoped_mmcss_registration.cc               \

SOURCE_BASE_CODEC_HEADERS +=                                                \
    $${_PRO_FILE_PWD_}/codec/audio_bus.h                                    \
    $${_PRO_FILE_PWD_}/codec/audio_decoder.h                                \
    $${_PRO_FILE_PWD_}/codec/audio_decoder_opus.h                           \
    $${_PRO_FILE_PWD_}/codec/audio_encoder.h                                \
    $${_PRO_FILE_PWD_}/codec/audio_encoder_opus.h                           \
    $${_PRO_FILE_PWD_}/codec/audio_sample_types.h                           \
    $${_PRO_FILE_PWD_}/codec/cursor_decoder.h                               \
    $${_PRO_FILE_PWD_}/codec/cursor_encoder.h                               \
    $${_PRO_FILE_PWD_}/codec/multi_channel_resampler.h                      \
    $${_PRO_FILE_PWD_}/codec/pixel_translator.h                             \
    $${_PRO_FILE_PWD_}/codec/scale_reducer.h                                \
    $${_PRO_FILE_PWD_}/codec/scoped_vpx_codec.h                             \
    $${_PRO_FILE_PWD_}/codec/scoped_zstd_stream.h                           \
    $${_PRO_FILE_PWD_}/codec/sinc_resampler.h                               \
    $${_PRO_FILE_PWD_}/codec/vector_math.h                                  \
    $${_PRO_FILE_PWD_}/codec/video_decoder.h                                \
    $${_PRO_FILE_PWD_}/codec/video_decoder_vpx.h                            \
    $${_PRO_FILE_PWD_}/codec/video_decoder_zstd.h                           \
    $${_PRO_FILE_PWD_}/codec/video_encoder.h                                \
    $${_PRO_FILE_PWD_}/codec/video_encoder_vpx.h                            \
    $${_PRO_FILE_PWD_}/codec/video_encoder_zstd.h                           \
    $${_PRO_FILE_PWD_}/codec/webm_file_muxer.h                              \
    $${_PRO_FILE_PWD_}/codec/webm_file_writer.h                             \
    $${_PRO_FILE_PWD_}/codec/webm_video_encoder.h                           \
    $${_PRO_FILE_PWD_}/codec/zstd_compress.h                                \

SOURCE_BASE_CODEC_SOURCES +=                                                \
    $${_PRO_FILE_PWD_}/codec/audio_bus.cc                                   \
    $${_PRO_FILE_PWD_}/codec/audio_decoder.cc                               \
    $${_PRO_FILE_PWD_}/codec/audio_decoder_opus.cc                          \
    $${_PRO_FILE_PWD_}/codec/audio_encoder_opus.cc                          \
    $${_PRO_FILE_PWD_}/codec/cursor_decoder.cc                              \
    $${_PRO_FILE_PWD_}/codec/cursor_encoder.cc                              \
    $${_PRO_FILE_PWD_}/codec/multi_channel_resampler.cc                     \
    $${_PRO_FILE_PWD_}/codec/pixel_translator.cc                            \
    $${_PRO_FILE_PWD_}/codec/scale_reducer.cc                               \
    $${_PRO_FILE_PWD_}/codec/scoped_vpx_codec.cc                            \
    $${_PRO_FILE_PWD_}/codec/scoped_zstd_stream.cc                          \
    $${_PRO_FILE_PWD_}/codec/sinc_resampler.cc                              \
    $${_PRO_FILE_PWD_}/codec/vector_math.cc                                 \
    $${_PRO_FILE_PWD_}/codec/video_decoder.cc                               \
    $${_PRO_FILE_PWD_}/codec/video_decoder_vpx.cc                           \
    $${_PRO_FILE_PWD_}/codec/video_decoder_zstd.cc                          \
    $${_PRO_FILE_PWD_}/codec/video_encoder.cc                               \
    $${_PRO_FILE_PWD_}/codec/video_encoder_vpx.cc                           \
    $${_PRO_FILE_PWD_}/codec/video_encoder_zstd.cc                          \
    $${_PRO_FILE_PWD_}/codec/webm_file_muxer.cc                             \
    $${_PRO_FILE_PWD_}/codec/webm_file_writer.cc                            \
    $${_PRO_FILE_PWD_}/codec/webm_video_encoder.cc                          \
    $${_PRO_FILE_PWD_}/codec/zstd_compress.cc                               \

SOURCE_BASE_CRYPTO_HEADERS +=                                               \
    $${_PRO_FILE_PWD_}/crypto/big_num.h                                     \
    $${_PRO_FILE_PWD_}/crypto/data_cryptor.h                                \
    $${_PRO_FILE_PWD_}/crypto/data_cryptor_chacha20_poly1305.h              \
    $${_PRO_FILE_PWD_}/crypto/data_cryptor_fake.h                           \
    $${_PRO_FILE_PWD_}/crypto/generic_hash.h                                \
    $${_PRO_FILE_PWD_}/crypto/key_pair.h                                    \
    $${_PRO_FILE_PWD_}/crypto/large_number_increment.h                      \
    $${_PRO_FILE_PWD_}/crypto/message_decryptor.h                           \
    $${_PRO_FILE_PWD_}/crypto/message_decryptor_fake.h                      \
    $${_PRO_FILE_PWD_}/crypto/message_encryptor.h                           \
    $${_PRO_FILE_PWD_}/crypto/message_decryptor_openssl.h                   \
    $${_PRO_FILE_PWD_}/crypto/message_encryptor_fake.h                      \
    $${_PRO_FILE_PWD_}/crypto/message_encryptor_openssl.h                   \
    $${_PRO_FILE_PWD_}/crypto/openssl_util.h                                \
    $${_PRO_FILE_PWD_}/crypto/os_crypt.h                                    \
    $${_PRO_FILE_PWD_}/crypto/password_generator.h                          \
    $${_PRO_FILE_PWD_}/crypto/password_hash.h                               \
    $${_PRO_FILE_PWD_}/crypto/random.h                                      \
    $${_PRO_FILE_PWD_}/crypto/scoped_crypto_initializer.h                   \
    $${_PRO_FILE_PWD_}/crypto/secure_memory.h                               \
    $${_PRO_FILE_PWD_}/crypto/srp_constants.h                               \
    $${_PRO_FILE_PWD_}/crypto/srp_math.h                                    \

SOURCE_BASE_CRYPTO_SOURCES +=                                               \
    $${_PRO_FILE_PWD_}/crypto/big_num.cc                                    \
    $${_PRO_FILE_PWD_}/crypto/data_cryptor_chacha20_poly1305.cc             \
    $${_PRO_FILE_PWD_}/crypto/data_cryptor_fake.cc                          \
    $${_PRO_FILE_PWD_}/crypto/generic_hash.cc                               \
    $${_PRO_FILE_PWD_}/crypto/key_pair.cc                                   \
    $${_PRO_FILE_PWD_}/crypto/large_number_increment.cc                     \
    $${_PRO_FILE_PWD_}/crypto/message_decryptor_fake.cc                     \
    $${_PRO_FILE_PWD_}/crypto/message_decryptor_openssl.cc                  \
    $${_PRO_FILE_PWD_}/crypto/message_encryptor_fake.cc                     \
    $${_PRO_FILE_PWD_}/crypto/message_encryptor_openssl.cc                  \
    $${_PRO_FILE_PWD_}/crypto/openssl_util.cc                               \
    $${_PRO_FILE_PWD_}/crypto/password_generator.cc                         \
    $${_PRO_FILE_PWD_}/crypto/password_hash.cc                              \
    $${_PRO_FILE_PWD_}/crypto/random.cc                                     \
    $${_PRO_FILE_PWD_}/crypto/scoped_crypto_initializer.cc                  \
    $${_PRO_FILE_PWD_}/crypto/secure_memory.cc                              \
    $${_PRO_FILE_PWD_}/crypto/srp_constants.cc                              \
    $${_PRO_FILE_PWD_}/crypto/srp_math.cc                                   \
    $${_PRO_FILE_PWD_}/crypto/os_crypt_win.cc                               \

SOURCE_BASE_DESKTOP_HEADERS +=                                              \
    $${_PRO_FILE_PWD_}/desktop/capture_scheduler.h                          \
    $${_PRO_FILE_PWD_}/desktop/desktop_environment.h                        \
    $${_PRO_FILE_PWD_}/desktop/desktop_resizer.h                            \
    $${_PRO_FILE_PWD_}/desktop/diff_block_32bpp_c.h                         \
    $${_PRO_FILE_PWD_}/desktop/diff_block_32bpp_sse2.h                      \
    $${_PRO_FILE_PWD_}/desktop/differ.h                                     \
    $${_PRO_FILE_PWD_}/desktop/frame.h                                      \
    $${_PRO_FILE_PWD_}/desktop/frame_aligned.h                              \
    $${_PRO_FILE_PWD_}/desktop/frame_rotation.h                             \
    $${_PRO_FILE_PWD_}/desktop/frame_simple.h                               \
    $${_PRO_FILE_PWD_}/desktop/geometry.h                                   \
    $${_PRO_FILE_PWD_}/desktop/mouse_cursor.h                               \
    $${_PRO_FILE_PWD_}/desktop/pixel_format.h                               \
    $${_PRO_FILE_PWD_}/desktop/power_save_blocker.h                         \
    $${_PRO_FILE_PWD_}/desktop/region.h                                     \
    $${_PRO_FILE_PWD_}/desktop/screen_capturer.h                            \
    $${_PRO_FILE_PWD_}/desktop/screen_capturer_helper.h                     \
    $${_PRO_FILE_PWD_}/desktop/screen_capturer_wrapper.h                    \
    $${_PRO_FILE_PWD_}/desktop/shared_frame.h                               \
    $${_PRO_FILE_PWD_}/desktop/shared_memory_frame.h                        \
    $${_PRO_FILE_PWD_}/desktop/desktop_environment_win.h                    \
    $${_PRO_FILE_PWD_}/desktop/desktop_resizer_win.h                        \
    $${_PRO_FILE_PWD_}/desktop/frame_dib.h                                  \
    $${_PRO_FILE_PWD_}/desktop/screen_capturer_dxgi.h                       \
    $${_PRO_FILE_PWD_}/desktop/screen_capturer_gdi.h                        \
    $${_PRO_FILE_PWD_}/desktop/screen_capturer_mirror.h                     \
    $${_PRO_FILE_PWD_}/desktop/win/bitmap_info.h                            \
    $${_PRO_FILE_PWD_}/desktop/win/cursor.h                                 \
    $${_PRO_FILE_PWD_}/desktop/win/d3d_device.h                             \
    $${_PRO_FILE_PWD_}/desktop/win/dfmirage.h                               \
    $${_PRO_FILE_PWD_}/desktop/win/dfmirage_helper.h                        \
    $${_PRO_FILE_PWD_}/desktop/win/display_configuration_monitor.h          \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_adapter_duplicator.h                \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_context.h                           \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_cursor.h                            \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_duplicator_controller.h             \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_frame.h                             \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_output_duplicator.h                 \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_texture.h                           \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_texture_mapping.h                   \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_texture_staging.h                   \
    $${_PRO_FILE_PWD_}/desktop/win/mirror_helper.h                          \
    $${_PRO_FILE_PWD_}/desktop/win/mv2.h                                    \
    $${_PRO_FILE_PWD_}/desktop/win/mv2_helper.h                             \
    $${_PRO_FILE_PWD_}/desktop/win/screen_capture_utils.h                   \

SOURCE_BASE_DESKTOP_SOURCES +=                                              \
    $${_PRO_FILE_PWD_}/desktop/capture_scheduler.cc                         \
    $${_PRO_FILE_PWD_}/desktop/desktop_environment.cc                       \
    $${_PRO_FILE_PWD_}/desktop/desktop_resizer.cc                           \
    $${_PRO_FILE_PWD_}/desktop/diff_block_32bpp_c.cc                        \
    $${_PRO_FILE_PWD_}/desktop/diff_block_32bpp_sse2.cc                     \
    $${_PRO_FILE_PWD_}/desktop/differ.cc                                    \
    $${_PRO_FILE_PWD_}/desktop/frame.cc                                     \
    $${_PRO_FILE_PWD_}/desktop/frame_aligned.cc                             \
    $${_PRO_FILE_PWD_}/desktop/frame_rotation.cc                            \
    $${_PRO_FILE_PWD_}/desktop/frame_simple.cc                              \
    $${_PRO_FILE_PWD_}/desktop/geometry.cc                                  \
    $${_PRO_FILE_PWD_}/desktop/mouse_cursor.cc                              \
    $${_PRO_FILE_PWD_}/desktop/pixel_format.cc                              \
    $${_PRO_FILE_PWD_}/desktop/power_save_blocker.cc                        \
    $${_PRO_FILE_PWD_}/desktop/region.cc                                    \
    $${_PRO_FILE_PWD_}/desktop/screen_capturer.cc                           \
    $${_PRO_FILE_PWD_}/desktop/screen_capturer_helper.cc                    \
    $${_PRO_FILE_PWD_}/desktop/screen_capturer_wrapper.cc                   \
    $${_PRO_FILE_PWD_}/desktop/shared_frame.cc                              \
    $${_PRO_FILE_PWD_}/desktop/shared_memory_frame.cc                       \
    $${_PRO_FILE_PWD_}/desktop/desktop_environment_win.cc                   \
    $${_PRO_FILE_PWD_}/desktop/desktop_resizer_win.cc                       \
    $${_PRO_FILE_PWD_}/desktop/frame_dib.cc                                 \
    $${_PRO_FILE_PWD_}/desktop/screen_capturer_dxgi.cc                      \
    $${_PRO_FILE_PWD_}/desktop/screen_capturer_gdi.cc                       \
    $${_PRO_FILE_PWD_}/desktop/screen_capturer_mirror.cc                    \
    $${_PRO_FILE_PWD_}/desktop/win/cursor.cc                                \
    $${_PRO_FILE_PWD_}/desktop/win/d3d_device.cc                            \
    $${_PRO_FILE_PWD_}/desktop/win/dfmirage_helper.cc                       \
    $${_PRO_FILE_PWD_}/desktop/win/display_configuration_monitor.cc         \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_adapter_duplicator.cc               \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_context.cc                          \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_cursor.cc                           \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_duplicator_controller.cc            \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_frame.cc                            \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_output_duplicator.cc                \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_texture.cc                          \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_texture_mapping.cc                  \
    $${_PRO_FILE_PWD_}/desktop/win/dxgi_texture_staging.cc                  \
    $${_PRO_FILE_PWD_}/desktop/win/mirror_helper.cc                         \
    $${_PRO_FILE_PWD_}/desktop/win/mv2_helper.cc                            \
    $${_PRO_FILE_PWD_}/desktop/win/screen_capture_utils.cc                  \

SOURCE_BASE_FILES_HEADERS +=                                                \
    $${_PRO_FILE_PWD_}/files/base_paths.h                                   \
    $${_PRO_FILE_PWD_}/files/file_path_watcher.h                            \
    $${_PRO_FILE_PWD_}/files/file_util.h                                    \
    $${_PRO_FILE_PWD_}/files/scoped_temp_file.h                             \

SOURCE_BASE_FILES_SOURCES +=                                                \
    $${_PRO_FILE_PWD_}/files/base_paths.cc                                  \
    $${_PRO_FILE_PWD_}/files/file_path_watcher.cc                           \
    $${_PRO_FILE_PWD_}/files/file_util.cc                                   \
    $${_PRO_FILE_PWD_}/files/scoped_temp_file.cc                            \
    $${_PRO_FILE_PWD_}/files/file_path_watcher_win.cc                       \

SOURCE_BASE_IPC_HEADERS +=                                                  \
    $${_PRO_FILE_PWD_}/ipc/ipc_channel.h                                    \
    $${_PRO_FILE_PWD_}/ipc/ipc_channel_proxy.h                              \
    $${_PRO_FILE_PWD_}/ipc/ipc_server.h                                     \
    $${_PRO_FILE_PWD_}/ipc/shared_memory.h                                  \
    $${_PRO_FILE_PWD_}/ipc/shared_memory_factory.h                          \
    $${_PRO_FILE_PWD_}/ipc/shared_memory_factory_proxy.h                    \

SOURCE_BASE_IPC_SOURCES +=                                                  \
    $${_PRO_FILE_PWD_}/ipc/ipc_channel.cc                                   \
    $${_PRO_FILE_PWD_}/ipc/ipc_channel_proxy.cc                             \
    $${_PRO_FILE_PWD_}/ipc/ipc_server.cc                                    \
    $${_PRO_FILE_PWD_}/ipc/shared_memory.cc                                 \
    $${_PRO_FILE_PWD_}/ipc/shared_memory_factory.cc                         \
    $${_PRO_FILE_PWD_}/ipc/shared_memory_factory_proxy.cc                   \

SOURCE_BASE_MEMORY_HEADERS +=                                               \
    $${_PRO_FILE_PWD_}/memory/aligned_memory.h                              \
    $${_PRO_FILE_PWD_}/memory/byte_array.h                                  \
    $${_PRO_FILE_PWD_}/memory/local_memory.h                                \
    $${_PRO_FILE_PWD_}/memory/typed_buffer.h                                \
    $${_PRO_FILE_PWD_}/memory/local_memory_impl/bad_local_weak_ptr.h        \
    $${_PRO_FILE_PWD_}/memory/local_memory_impl/checked_delete.h            \
    $${_PRO_FILE_PWD_}/memory/local_memory_impl/enable_shared_from_this.h   \
    $${_PRO_FILE_PWD_}/memory/local_memory_impl/local_shared_ptr.h          \
    $${_PRO_FILE_PWD_}/memory/local_memory_impl/local_weak_ptr.h            \
    $${_PRO_FILE_PWD_}/memory/local_memory_impl/make_local_shared.h         \
    $${_PRO_FILE_PWD_}/memory/local_memory_impl/shared_count.h              \
    $${_PRO_FILE_PWD_}/memory/local_memory_impl/sp_convertible.h            \
    $${_PRO_FILE_PWD_}/memory/local_memory_impl/sp_counted_base_nt.h        \
    $${_PRO_FILE_PWD_}/memory/local_memory_impl/sp_counted_impl.h           \

SOURCE_BASE_MEMORY_SOURCES +=                                               \
    $${_PRO_FILE_PWD_}/memory/aligned_memory.cc                             \
    $${_PRO_FILE_PWD_}/memory/byte_array.cc                                 \

SOURCE_BASE_MESSAGE_LOOP_HEADERS +=                                         \
    $${_PRO_FILE_PWD_}/message_loop/message_loop.h                          \
    $${_PRO_FILE_PWD_}/message_loop/message_loop_task_runner.h              \
    $${_PRO_FILE_PWD_}/message_loop/message_pump.h                          \
    $${_PRO_FILE_PWD_}/message_loop/message_pump_asio.h                     \
    $${_PRO_FILE_PWD_}/message_loop/message_pump_default.h                  \
    $${_PRO_FILE_PWD_}/message_loop/message_pump_dispatcher.h               \
    $${_PRO_FILE_PWD_}/message_loop/pending_task.h                          \
    $${_PRO_FILE_PWD_}/message_loop/message_pump_win.h                      \

SOURCE_BASE_MESSAGE_LOOP_SOURCES +=                                         \
    $${_PRO_FILE_PWD_}/message_loop/message_loop.cc                         \
    $${_PRO_FILE_PWD_}/message_loop/message_loop_task_runner.cc             \
    $${_PRO_FILE_PWD_}/message_loop/message_pump_asio.cc                    \
    $${_PRO_FILE_PWD_}/message_loop/message_pump_default.cc                 \
    $${_PRO_FILE_PWD_}/message_loop/pending_task.cc                         \
    $${_PRO_FILE_PWD_}/message_loop/message_pump_win.cc                     \

SOURCE_BASE_NET_HEADERS +=                                                  \
    $${_PRO_FILE_PWD_}/net/adapter_enumerator.h                             \
    $${_PRO_FILE_PWD_}/net/address.h                                        \
    $${_PRO_FILE_PWD_}/net/curl_util.h                                      \
    $${_PRO_FILE_PWD_}/net/ip_util.h                                        \
    $${_PRO_FILE_PWD_}/net/network_channel.h                                \
    $${_PRO_FILE_PWD_}/net/tcp_channel.h                                    \
    $${_PRO_FILE_PWD_}/net/tcp_channel_proxy.h                              \
    $${_PRO_FILE_PWD_}/net/tcp_server.h                                     \
    $${_PRO_FILE_PWD_}/net/variable_size.h                                  \
    $${_PRO_FILE_PWD_}/net/write_task.h                                     \
    $${_PRO_FILE_PWD_}/net/connect_enumerator.h                             \
    $${_PRO_FILE_PWD_}/net/firewall_manager.h                               \
    $${_PRO_FILE_PWD_}/net/open_files_enumerator.h                          \
    $${_PRO_FILE_PWD_}/net/route_enumerator.h                               \

SOURCE_BASE_NET_SOURCES +=                                                  \
    $${_PRO_FILE_PWD_}/net/adapter_enumerator.cc                            \
    $${_PRO_FILE_PWD_}/net/address.cc                                       \
    $${_PRO_FILE_PWD_}/net/curl_util.cc                                     \
    $${_PRO_FILE_PWD_}/net/ip_util.cc                                       \
    $${_PRO_FILE_PWD_}/net/network_channel.cc                               \
    $${_PRO_FILE_PWD_}/net/tcp_channel.cc                                   \
    $${_PRO_FILE_PWD_}/net/tcp_channel_proxy.cc                             \
    $${_PRO_FILE_PWD_}/net/tcp_server.cc                                    \
    $${_PRO_FILE_PWD_}/net/variable_size.cc                                 \
    $${_PRO_FILE_PWD_}/net/connect_enumerator.cc                            \
    $${_PRO_FILE_PWD_}/net/firewall_manager.cc                              \
    $${_PRO_FILE_PWD_}/net/open_files_enumerator.cc                         \
    $${_PRO_FILE_PWD_}/net/route_enumerator.cc                              \

SOURCE_BASE_PEER_HEADERS +=                                                 \
    $${_PRO_FILE_PWD_}/peer/authenticator.h                                 \
    $${_PRO_FILE_PWD_}/peer/client_authenticator.h                          \
    $${_PRO_FILE_PWD_}/peer/host_id.h                                       \
    $${_PRO_FILE_PWD_}/peer/relay_peer.h                                    \
    $${_PRO_FILE_PWD_}/peer/relay_peer_manager.h                            \
    $${_PRO_FILE_PWD_}/peer/server_authenticator.h                          \
    $${_PRO_FILE_PWD_}/peer/server_authenticator_manager.h                  \
    $${_PRO_FILE_PWD_}/peer/user.h                                          \
    $${_PRO_FILE_PWD_}/peer/user_list.h                                     \
    $${_PRO_FILE_PWD_}/peer/user_list_base.h                                \

SOURCE_BASE_PEER_SOURCES +=                                                 \
    $${_PRO_FILE_PWD_}/peer/authenticator.cc                                \
    $${_PRO_FILE_PWD_}/peer/client_authenticator.cc                         \
    $${_PRO_FILE_PWD_}/peer/host_id.cc                                      \
    $${_PRO_FILE_PWD_}/peer/relay_peer.cc                                   \
    $${_PRO_FILE_PWD_}/peer/relay_peer_manager.cc                           \
    $${_PRO_FILE_PWD_}/peer/server_authenticator.cc                         \
    $${_PRO_FILE_PWD_}/peer/server_authenticator_manager.cc                 \
    $${_PRO_FILE_PWD_}/peer/user.cc                                         \
    $${_PRO_FILE_PWD_}/peer/user_list.cc                                    \

SOURCE_BASE_SETTINGS_HEADERS +=                                             \
    $${_PRO_FILE_PWD_}/settings/json_settings.h                             \
    $${_PRO_FILE_PWD_}/settings/settings.h                                  \

SOURCE_BASE_SETTINGS_SOURCES +=                                             \
    $${_PRO_FILE_PWD_}/settings/json_settings.cc                            \
    $${_PRO_FILE_PWD_}/settings/settings.cc                                 \

SOURCE_BASE_STRINGS_HEADERS +=                                              \
    $${_PRO_FILE_PWD_}/strings/strcat.h                                     \
    $${_PRO_FILE_PWD_}/strings/string_number_conversions.h                  \
    $${_PRO_FILE_PWD_}/strings/string_printf.h                              \
    $${_PRO_FILE_PWD_}/strings/string_split.h                               \
    $${_PRO_FILE_PWD_}/strings/string_util_constants.h                      \
    $${_PRO_FILE_PWD_}/strings/string_util.h                                \
    $${_PRO_FILE_PWD_}/strings/unicode.h                                    \

SOURCE_BASE_STRINGS_SOURCES +=                                              \
    $${_PRO_FILE_PWD_}/strings/strcat.cc                                    \
    $${_PRO_FILE_PWD_}/strings/string_number_conversions.cc                 \
    $${_PRO_FILE_PWD_}/strings/string_printf.cc                             \
    $${_PRO_FILE_PWD_}/strings/string_split.cc                              \
    $${_PRO_FILE_PWD_}/strings/string_util.cc                               \
    $${_PRO_FILE_PWD_}/strings/string_util_constants.cc                     \
    $${_PRO_FILE_PWD_}/strings/unicode.cc                                   \
    $${_PRO_FILE_PWD_}/strings/string_util_win.cc                           \

SOURCE_BASE_THREADING_HEADERS +=                                            \
    $${_PRO_FILE_PWD_}/threading/simple_thread.h                            \
    $${_PRO_FILE_PWD_}/threading/thread.h                                   \
    $${_PRO_FILE_PWD_}/threading/thread_checker.h                           \

SOURCE_BASE_THREADING_SOURCES +=                                            \
    $${_PRO_FILE_PWD_}/threading/simple_thread.cc                           \
    $${_PRO_FILE_PWD_}/threading/thread.cc                                  \
    $${_PRO_FILE_PWD_}/threading/thread_checker.cc                          \

$${upper($${TARGET})}_HEADERS +=                \
    $$SOURCE_BASE_HEADERS                       \
    $$SOURCE_BASE_AUDIO_HEADERS                 \
    $$SOURCE_BASE_CODEC_HEADERS                 \
    $$SOURCE_BASE_CRYPTO_HEADERS                \
    $$SOURCE_BASE_DESKTOP_HEADERS               \
    $$SOURCE_BASE_FILES_HEADERS                 \
    $$SOURCE_BASE_IPC_HEADERS                   \
    $$SOURCE_BASE_MEMORY_HEADERS                \
    $$SOURCE_BASE_MESSAGE_LOOP_HEADERS          \
    $$SOURCE_BASE_NET_HEADERS                   \
    $$SOURCE_BASE_PEER_HEADERS                  \
    $$SOURCE_BASE_SETTINGS_HEADERS              \
    $$SOURCE_BASE_STRINGS_HEADERS               \
    $$SOURCE_BASE_THREADING_HEADERS

$${upper($${TARGET})}_SOURCES +=                \
    $$SOURCE_BASE_SOURCES                       \
    $$SOURCE_BASE_AUDIO_SOURCES                 \
    $$SOURCE_BASE_CODEC_SOURCES                 \
    $$SOURCE_BASE_CRYPTO_SOURCES                \
    $$SOURCE_BASE_DESKTOP_SOURCES               \
    $$SOURCE_BASE_FILES_SOURCES                 \
    $$SOURCE_BASE_IPC_SOURCES                   \
    $$SOURCE_BASE_MEMORY_SOURCES                \
    $$SOURCE_BASE_MESSAGE_LOOP_SOURCES          \
    $$SOURCE_BASE_NET_SOURCES                   \
    $$SOURCE_BASE_PEER_SOURCES                  \
    $$SOURCE_BASE_SETTINGS_SOURCES              \
    $$SOURCE_BASE_STRINGS_SOURCES               \
    $$SOURCE_BASE_THREADING_SOURCES
