// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef ENABLE_METRICS_PREVIEW
#  include "opentelemetry/common/spin_lock_mutex.h"
#  include "opentelemetry/sdk/metrics/aggregation/aggregation.h"

#  include <mutex>

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{

class LongHistogramAggregation : public Aggregation
{
public:
  LongHistogramAggregation();
  LongHistogramAggregation(HistogramPointData &&);

  void Aggregate(long value, const PointAttributes &attributes = {}) noexcept override;

  void Aggregate(double value, const PointAttributes &attributes = {}) noexcept override {}

  virtual std::unique_ptr<Aggregation> Merge(const Aggregation &delta) const noexcept override;

  virtual std::unique_ptr<Aggregation> Diff(const Aggregation &next) const noexcept override;

  PointType ToPoint() const noexcept override;

private:
  opentelemetry::common::SpinLockMutex lock_;
  HistogramPointData point_data_;
};

class DoubleHistogramAggregation : public Aggregation
{
public:
  DoubleHistogramAggregation();
  DoubleHistogramAggregation(HistogramPointData &&);

  void Aggregate(long value, const PointAttributes &attributes = {}) noexcept override {}

  void Aggregate(double value, const PointAttributes &attributes = {}) noexcept override;

  virtual std::unique_ptr<Aggregation> Merge(const Aggregation &delta) const noexcept override;

  virtual std::unique_ptr<Aggregation> Diff(const Aggregation &next) const noexcept override;

  PointType ToPoint() const noexcept override;

private:
  mutable opentelemetry::common::SpinLockMutex lock_;
  mutable HistogramPointData point_data_;
};

}  // namespace metrics
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
#endif