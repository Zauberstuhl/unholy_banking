/*
 * NodeJS wrapper-plugin for Aqbanking
 * Copyright (C) 2015  Lukas Matt <lukas@zauberstuhl.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <node.h>
#include <v8.h>

#include <iostream>

#include "ab_helpers.h"

using namespace std;
using namespace v8;

void AB_listaccounts(const v8::FunctionCallbackInfo<Value>& args) {
  UB::Helper helper;
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(helper.list_accounts(isolate));
  // close class and free stuff
  if (helper.close() != 0) {
    cout << "Something went wrong while closing.." << endl;
  }
}

void Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  // register listAccounts function
  exports->Set(String::NewFromUtf8(isolate, "listAccounts"),
      FunctionTemplate::New(isolate, AB_listaccounts)->GetFunction());
}

NODE_MODULE(unholy_banking, Init)
