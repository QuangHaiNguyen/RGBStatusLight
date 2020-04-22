var group___o_t_a_t_y_p_e_d_e_f =
[
    [ "tstrOtaInitHdr", "structtstr_ota_init_hdr.html", [
      [ "u32OtaMagicValue", "structtstr_ota_init_hdr.html#ac2f6101ff1872f1a3450a51453cfa92f", null ],
      [ "u32OtaPayloadSize", "structtstr_ota_init_hdr.html#aaa9e3fa043f203dcbbce2b5837ebccf7", null ]
    ] ],
    [ "tstrOtaControlSec", "structtstr_ota_control_sec.html", [
      [ "u32OtaControlSecCrc", "structtstr_ota_control_sec.html#a7a9d3b362e97e02ce62d1c3919c60325", null ],
      [ "u32OtaCortusAppRollbackOffset", "structtstr_ota_control_sec.html#a510e1e11a535437ed114b3c75de0c0ea", null ],
      [ "u32OtaCortusAppRollbackValidSts", "structtstr_ota_control_sec.html#a79d83ba3e3ff396cc132f4139888e2d3", null ],
      [ "u32OtaCortusAppRollbackVer", "structtstr_ota_control_sec.html#ac36a19c206d67ddf681712c9dba9b792", null ],
      [ "u32OtaCortusAppWorkingOffset", "structtstr_ota_control_sec.html#a70d73f29b9bbd6622bb7cdaa18eba333", null ],
      [ "u32OtaCortusAppWorkingValidSts", "structtstr_ota_control_sec.html#a8dd67f701ac86388c4b2c9a264513727", null ],
      [ "u32OtaCortusAppWorkingVer", "structtstr_ota_control_sec.html#ab1e38e14e6201ce323bfb7dc65885fca", null ],
      [ "u32OtaCurrentWorkingImagFirmwareVer", "structtstr_ota_control_sec.html#a39187b8a5250c90cecd0209d266a1c53", null ],
      [ "u32OtaCurrentWorkingImagOffset", "structtstr_ota_control_sec.html#a0b5890ab4637245a08e221b8f0b6a1fb", null ],
      [ "u32OtaFormatVersion", "structtstr_ota_control_sec.html#a3b10d0d1a8cbf47a93485411ca1c7d3a", null ],
      [ "u32OtaLastCheckTime", "structtstr_ota_control_sec.html#adeeae383eb4c6161bc0faac5120a42bd", null ],
      [ "u32OtaMagicValue", "structtstr_ota_control_sec.html#ac2f6101ff1872f1a3450a51453cfa92f", null ],
      [ "u32OtaRollbackImageOffset", "structtstr_ota_control_sec.html#aed3cbcd4651d1e0e2b6abdaf973e6b2e", null ],
      [ "u32OtaRollbackImageValidStatus", "structtstr_ota_control_sec.html#a96d3e8a1351043363233248a330eb2d7", null ],
      [ "u32OtaRollbackImagFirmwareVer", "structtstr_ota_control_sec.html#a1897969d484384c08d9403cf6ef3b2dc", null ],
      [ "u32OtaSequenceNumber", "structtstr_ota_control_sec.html#acd45c85b3ffb3759024c6a7ce7499375", null ]
    ] ],
    [ "tstrOtaUpdateStatusResp", "structtstr_ota_update_status_resp.html", [
      [ "_PAD16_", "structtstr_ota_update_status_resp.html#af83cb104105cf5c3207022d1d72b323a", null ],
      [ "u8OtaUpdateStatus", "structtstr_ota_update_status_resp.html#a17b93f434fabc4852ca83f713a883054", null ],
      [ "u8OtaUpdateStatusType", "structtstr_ota_update_status_resp.html#a0f628b4bd142ecc149589540e5857822", null ]
    ] ],
    [ "tstrOtaUpdateInfo", "structtstr_ota_update_info.html", [
      [ "__PAD8__", "structtstr_ota_update_info.html#a5afabed135c09b9f2a1b2ed6954e2931", null ],
      [ "u8DownloadUrlOffset", "structtstr_ota_update_info.html#a0aac130b54954f81c8c360032ce12b05", null ],
      [ "u8DownloadUrlSize", "structtstr_ota_update_info.html#a1f7a9af78b6039a1ca3c717738d25ed3", null ],
      [ "u8NcdRequiredUpgrade", "structtstr_ota_update_info.html#a80a1c9784cb5f86db968107b610ce4c2", null ],
      [ "u8NcdUpgradeVersion", "structtstr_ota_update_info.html#a2450b871b70094fe6da91ee3be3b1ede", null ],
      [ "u8NcfCurrentVersion", "structtstr_ota_update_info.html#a324facfa3010a76980c8eab367f93210", null ],
      [ "u8NcfUpgradeVersion", "structtstr_ota_update_info.html#acd22e0ecac48c783b663f366e4587f6d", null ]
    ] ],
    [ "tstrOtaHostFileGetStatusResp", "structtstr_ota_host_file_get_status_resp.html", [
      [ "__PAD16__", "structtstr_ota_host_file_get_status_resp.html#a6d699da96dffccfccb23cf9164464189", null ],
      [ "u32OtaFileSize", "structtstr_ota_host_file_get_status_resp.html#a31b7b099168183c15007c862b75fda36", null ],
      [ "u8CFHandler", "structtstr_ota_host_file_get_status_resp.html#a844dd4ed104e49921d1e362bbc86e1e8", null ],
      [ "u8OtaFileGetStatus", "structtstr_ota_host_file_get_status_resp.html#a8d0ba451c024ba125cbaaaec5b6f5dff", null ]
    ] ],
    [ "tstrOtaHostFileReadStatusResp", "structtstr_ota_host_file_read_status_resp.html", [
      [ "__PAD8__", "structtstr_ota_host_file_read_status_resp.html#a5afabed135c09b9f2a1b2ed6954e2931", null ],
      [ "pFileBuf", "structtstr_ota_host_file_read_status_resp.html#a6fc81fb8f52df462747ea68bc3cb54ce", null ],
      [ "u16FileBlockSz", "structtstr_ota_host_file_read_status_resp.html#aa70ee62f4cab7ee2f2396030380fb921", null ],
      [ "u8OtaFileReadStatus", "structtstr_ota_host_file_read_status_resp.html#ac04f4c440bf4fe47ca4b3967c1a0c6b4", null ]
    ] ],
    [ "tstrOtaHostFileEraseStatusResp", "structtstr_ota_host_file_erase_status_resp.html", [
      [ "__PAD24__", "structtstr_ota_host_file_erase_status_resp.html#aa5a8cce92864d5c9acd5c53b25370d90", null ],
      [ "u8OtaFileEraseStatus", "structtstr_ota_host_file_erase_status_resp.html#a721bc063d048c8213fd9e8e9089de616", null ]
    ] ],
    [ "tenuM2mOtaCmd", "group___o_t_a_t_y_p_e_d_e_f.html#ga0220996b43dbde1d7e6d6870fafd245c", [
      [ "M2M_OTA_REQ_START_FW_UPDATE", "group___o_t_a_t_y_p_e_d_e_f.html#gga0220996b43dbde1d7e6d6870fafd245ca08a38fb4c966098d1bbd5d1975bd6830", null ],
      [ "M2M_OTA_REQ_SWITCH_FIRMWARE", "group___o_t_a_t_y_p_e_d_e_f.html#gga0220996b43dbde1d7e6d6870fafd245ca1230a122c8305cdc8f8ea4bab675838f", null ],
      [ "M2M_OTA_REQ_ROLLBACK_FW", "group___o_t_a_t_y_p_e_d_e_f.html#gga0220996b43dbde1d7e6d6870fafd245cae10bafa493a56f584f5fe1f0916a26b8", null ],
      [ "M2M_OTA_RESP_UPDATE_STATUS", "group___o_t_a_t_y_p_e_d_e_f.html#gga0220996b43dbde1d7e6d6870fafd245ca631643e3dd7cd16ee951f2c353ab5e05", null ],
      [ "M2M_OTA_REQ_ABORT", "group___o_t_a_t_y_p_e_d_e_f.html#gga0220996b43dbde1d7e6d6870fafd245cad1aa4fb98683f0b01b99f28f8d458f66", null ]
    ] ],
    [ "tenuOtaError", "group___o_t_a_t_y_p_e_d_e_f.html#ga10cf5c26f12c365228c95bd0bcf20704", [
      [ "OTA_SUCCESS", "group___o_t_a_t_y_p_e_d_e_f.html#gga10cf5c26f12c365228c95bd0bcf20704ac21cbee99dd60c7ba62544609bfd8bb1", null ],
      [ "OTA_ERR_WORKING_IMAGE_LOAD_FAIL", "group___o_t_a_t_y_p_e_d_e_f.html#gga10cf5c26f12c365228c95bd0bcf20704a52814139590eb930a26ea2e3cc350573", null ],
      [ "OTA_ERR_INVALID_CONTROL_SEC", "group___o_t_a_t_y_p_e_d_e_f.html#gga10cf5c26f12c365228c95bd0bcf20704a8478d546630512b462b8f59a196e9b51", null ],
      [ "M2M_ERR_OTA_SWITCH_FAIL", "group___o_t_a_t_y_p_e_d_e_f.html#gga10cf5c26f12c365228c95bd0bcf20704a07bee676bfa7f90fb15cb35a7273a1e7", null ],
      [ "M2M_ERR_OTA_START_UPDATE_FAIL", "group___o_t_a_t_y_p_e_d_e_f.html#gga10cf5c26f12c365228c95bd0bcf20704ac3dd21c2c485e62f43316f35b5c728ac", null ],
      [ "M2M_ERR_OTA_ROLLBACK_FAIL", "group___o_t_a_t_y_p_e_d_e_f.html#gga10cf5c26f12c365228c95bd0bcf20704a46882850a7e6a7251cde16a0687fde27", null ],
      [ "M2M_ERR_OTA_INVALID_FLASH_SIZE", "group___o_t_a_t_y_p_e_d_e_f.html#gga10cf5c26f12c365228c95bd0bcf20704aca98330ad81ed1a75ba5fe4ec5e8514d", null ],
      [ "M2M_ERR_OTA_INVALID_ARG", "group___o_t_a_t_y_p_e_d_e_f.html#gga10cf5c26f12c365228c95bd0bcf20704a53a587b0cde221dedacff73fbd5ca25b", null ],
      [ "M2M_ERR_OTA_INPROGRESS", "group___o_t_a_t_y_p_e_d_e_f.html#gga10cf5c26f12c365228c95bd0bcf20704a98c737cb70de854cdf1e46e54ed96675", null ]
    ] ],
    [ "tenuOtaUpdateStatus", "group___o_t_a_t_y_p_e_d_e_f.html#gab7006b9cb55eb414d0416d0513533eeb", [
      [ "OTA_STATUS_SUCCESS", "group___o_t_a_t_y_p_e_d_e_f.html#ggab7006b9cb55eb414d0416d0513533eeba23e293bcc679d3021e202ac255b71500", null ],
      [ "OTA_STATUS_FAIL", "group___o_t_a_t_y_p_e_d_e_f.html#ggab7006b9cb55eb414d0416d0513533eeba54701f32696891a07b613bb157301c27", null ],
      [ "OTA_STATUS_INVALID_ARG", "group___o_t_a_t_y_p_e_d_e_f.html#ggab7006b9cb55eb414d0416d0513533eebaa3dcfcfc38c37e071acd2f2d8ff910b0", null ],
      [ "OTA_STATUS_INVALID_RB_IMAGE", "group___o_t_a_t_y_p_e_d_e_f.html#ggab7006b9cb55eb414d0416d0513533eebae5855cff1caaff00ab7397c9c018eb58", null ],
      [ "OTA_STATUS_INVALID_FLASH_SIZE", "group___o_t_a_t_y_p_e_d_e_f.html#ggab7006b9cb55eb414d0416d0513533eebab4e012e48969bd9c021049b31f3f0afd", null ],
      [ "OTA_STATUS_ALREADY_ENABLED", "group___o_t_a_t_y_p_e_d_e_f.html#ggab7006b9cb55eb414d0416d0513533eebaf72b28a675a14010168519a66fabbfaa", null ],
      [ "OTA_STATUS_UPDATE_INPROGRESS", "group___o_t_a_t_y_p_e_d_e_f.html#ggab7006b9cb55eb414d0416d0513533eeba5143e975d62ec1b36c14e37f2553ad88", null ],
      [ "OTA_STATUS_IMAGE_VERIF_FAILED", "group___o_t_a_t_y_p_e_d_e_f.html#ggab7006b9cb55eb414d0416d0513533eeba3f3d7683fd8ee3d026cad78bfccf0457", null ],
      [ "OTA_STATUS_CONNECTION_ERROR", "group___o_t_a_t_y_p_e_d_e_f.html#ggab7006b9cb55eb414d0416d0513533eeba62b5257f5bfc53c725ee131ffde2b923", null ],
      [ "OTA_STATUS_SERVER_ERROR", "group___o_t_a_t_y_p_e_d_e_f.html#ggab7006b9cb55eb414d0416d0513533eebac8fdd2b0a2fa284faa697b379382f78a", null ],
      [ "OTA_STATUS_ABORTED", "group___o_t_a_t_y_p_e_d_e_f.html#ggab7006b9cb55eb414d0416d0513533eeba3b068b19f0fecbf86a381348fc389846", null ]
    ] ],
    [ "tenuOtaUpdateStatusType", "group___o_t_a_t_y_p_e_d_e_f.html#ga3e56744d263918b9e36016f78d823c3a", [
      [ "DL_STATUS", "group___o_t_a_t_y_p_e_d_e_f.html#gga3e56744d263918b9e36016f78d823c3aa9b634fb58a53969f9af8a89908e58c5e", null ],
      [ "SW_STATUS", "group___o_t_a_t_y_p_e_d_e_f.html#gga3e56744d263918b9e36016f78d823c3aa2f1dabb326d861eadb5a5cd1b41962ff", null ],
      [ "RB_STATUS", "group___o_t_a_t_y_p_e_d_e_f.html#gga3e56744d263918b9e36016f78d823c3aad9b2f16f8c41c4108806a4c78dea422c", null ],
      [ "AB_STATUS", "group___o_t_a_t_y_p_e_d_e_f.html#gga3e56744d263918b9e36016f78d823c3aa0b4e411fb407bc62bf6b94175158862c", null ],
      [ "HFD_STATUS", "group___o_t_a_t_y_p_e_d_e_f.html#gga3e56744d263918b9e36016f78d823c3aaa125479191f24a910fc75ee33de0a1d4", null ]
    ] ]
];