#ifndef PIPELINE_STAGE_H_
#define PIPELINE_STAGE_H_

class PipelineStage {
 private:
  /// Bank of priority queues
  std::vector<PriorityQueue> priority_queue_bank_;

  /// Bank of calendar queues
  std::vector<CalendarQueue> calendar_queue_bank_;
};

#endif  // PIPELINE_STAGE_H_
