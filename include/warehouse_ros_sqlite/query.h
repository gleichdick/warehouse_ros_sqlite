// SPDX-License-Identifier: BSD-3-Clause

/*
 * Copyright (c) 2020, Bjarne von Horn
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of the copyright holder nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BJARNE VON HORN BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once

#include <warehouse_ros/metadata.h>

#include <boost/variant.hpp>
#include <sstream>

#include <warehouse_ros_sqlite/utils.h>

namespace warehouse_ros_sqlite
{
class Query : public warehouse_ros::Query
{
public:
  Query();
  using Variant = boost::variant<std::string, double, int>;
  void append(const std::string& name, const std::string& val) override;
  void append(const std::string& name, const double val) override;
  void append(const std::string& name, const int val) override;
  void append(const std::string& name, const bool val) override;
  void appendLT(const std::string& name, const double val) override;
  void appendLT(const std::string& name, const int val) override;
  void appendLTE(const std::string& name, const double val) override;
  void appendLTE(const std::string& name, const int val) override;
  void appendGT(const std::string& name, const double val) override;
  void appendGT(const std::string& name, const int val) override;
  void appendGTE(const std::string& name, const double val) override;
  void appendGTE(const std::string& name, const int val) override;
  void appendRange(const std::string& name, const double lower, const double upper) override;
  void appendRange(const std::string& name, const int lower, const int upper) override;
  void appendRangeInclusive(const std::string& name, const double lower, const double upper) override;
  void appendRangeInclusive(const std::string& name, const int lower, const int upper) override;

  sqlite3_stmt_ptr prepare(sqlite3* db_conn, const std::string& intro, const std::string& outro = "",
                           int bind_start_col = 1) const;

private:
  template <typename T>
  void doappend(const std::string& name, const char* op, T val)
  {
    if (!values_.empty())
      query_ << " AND ";
    values_.emplace_back(val);
    query_ << schema::METADATA_COLUMN_PREFIX << name << op << '?';
  }
  std::vector<Variant> values_;
  std::stringstream query_;
};

}  // namespace warehouse_ros_sqlite
