#ifndef PIFO_PIPELINE_STAGE_H_
#define PIFO_PIPELINE_STAGE_H_

class PIFOPipelineStage {
 private:
  /// Bank of priority queues
  std::vector<PriorityQueue> priority_queue_bank_ = {};

  /// Bank of calendar queues
  std::vector<CalendarQueue> calendar_queue_bank_ = {};
};

#endif  // PIFO_PIPELINE_STAGE_H_
