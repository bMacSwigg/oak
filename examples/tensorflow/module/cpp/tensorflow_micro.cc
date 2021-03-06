/*
 * Copyright 2020 The Project Oak Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stddef.h>
#include <stdint.h>

#include "oak/module/oak_abi.h"
#include "oak/module/placeholders.h"
#include "tensorflow/lite/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"

// Include standard C++ placeholder oak_main() implementation.
#include "oak/module/oak_main.h"

// Constants were taken from the TFLite exapmles:
// https://github.com/tensorflow/tensorflow/blob/11bed638b14898cdde967f6b108e45732aa4798a/tensorflow/lite/micro/examples/network_tester/network_tester_test.cc#L25
// https://github.com/tensorflow/tensorflow/blob/11bed638b14898cdde967f6b108e45732aa4798a/tensorflow/lite/micro/examples/network_tester/network_model.h#L16-L64
const uint16_t kTensorArenaSize = 1024;

const unsigned char kModelBuffer[] = {
    0x18, 0x00, 0x00, 0x00, 0x54, 0x46, 0x4c, 0x33, 0x00, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x04, 0x00,
    0x08, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x14, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x08, 0x02, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x54, 0x4f, 0x43, 0x4f,
    0x20, 0x43, 0x6f, 0x6e, 0x76, 0x65, 0x72, 0x74, 0x65, 0x64, 0x2e, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x18, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff,
    0xfc, 0xff, 0xff, 0xff, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 0xf8, 0xfe, 0xff, 0xff,
    0x20, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x3c, 0x01, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 0x7e, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x03, 0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x64, 0x61, 0x74, 0x61,
    0x2f, 0x50, 0x6c, 0x61, 0x63, 0x65, 0x68, 0x6f, 0x6c, 0x64, 0x65, 0x72, 0x00, 0x00, 0x00, 0x00,
    0x6c, 0xff, 0xff, 0xff, 0x30, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7f, 0x43, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
    0x18, 0x00, 0x08, 0x00, 0x07, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x14, 0x00, 0x0e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x70, 0x6f, 0x6f, 0x6c,
    0x31, 0x2f, 0x4d, 0x61, 0x78, 0x50, 0x6f, 0x6f, 0x6c, 0x32, 0x44, 0x2f, 0x4d, 0x61, 0x78, 0x50,
    0x6f, 0x6f, 0x6c, 0x00, 0x0c, 0x00, 0x14, 0x00, 0x04, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x43,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x14, 0x00, 0x18, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x14, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x10, 0x00, 0x00, 0x00,
    0x14, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x07, 0x00, 0x08, 0x00, 0x0c, 0x00, 0x10, 0x00, 0x14, 0x00,
    0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x07, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11};

const unsigned char kInputData[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
const unsigned char kExpectedOutputData[] = {6, 8, 14, 16};

std::string init_tensorflow() {
  const tflite::Model* model = ::tflite::GetModel(kModelBuffer);

  tflite::ops::micro::AllOpsResolver resolver;

  // TensorFlow Lite for Microcontrollers requires manual memory allocation:
  // https://www.tensorflow.org/lite/microcontrollers#limitations
  uint8_t tensor_arena[kTensorArenaSize];
  tflite::MicroInterpreter interpreter(model, resolver, tensor_arena, kTensorArenaSize, nullptr);
  interpreter.AllocateTensors();

  TfLiteTensor* input = interpreter.input(0);
  memcpy(input->data.uint8, kInputData, input->bytes);

  TfLiteStatus invoke_status = interpreter.Invoke();
  if (invoke_status != kTfLiteOk) {
    return std::string("Error: Interpreter invoke failed");
  }

  TfLiteTensor* output = interpreter.output(0);
  if (memcmp(kExpectedOutputData, output->data.uint8, output->bytes) != 0) {
    return std::string("Error: Model output is incorrect");
  }
  return std::string("Success: Model was loaded correctly");
}

extern "C" void process_invocation(const uint8_t* _req_buf, uint32_t _req_size,
                                   oak_abi::Handle rsp_handle) {
  init_tensorflow();

  // Manually create an encapsulated GrpcResponse protobuf and send it back.
  //    0a                 b00001.010 = tag 1 (GrpcResponse.rsp_msg), length-delimited field
  //    0b                 length=11
  //      12                 b00010.010 = tag 2 (Any.value), length-delimited field
  //      09                 length=9
  //        0A                 b00001.010 = tag 1 (HelloResponse.reply), length-delimited field
  //        07                 length=7
  //          74657374696e67   "testing"
  //    18                 b00011.000 = tag 3 (GrpcResponse.last), varint
  //    01                 true
  uint8_t rsp_buf[] = "\x0a\x0b\x12\x09\x0A\x07\x74\x65\x73\x74\x69\x6e\x67\x18\x01";
  // TODO(#422): replace with use of message type and serialization.
  channel_write(rsp_handle, rsp_buf, sizeof(rsp_buf) - 1, nullptr, 0);
}
