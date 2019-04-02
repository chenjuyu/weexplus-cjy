/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#pragma once

#include "ObjectPropertyCondition.h"
#include "Watchpoint.h"
#include <wtf/FastMalloc.h>
#include <wtf/Noncopyable.h>

namespace JSC {

class AdaptiveInferredPropertyValueWatchpointBase {
    WTF_MAKE_NONCOPYABLE(AdaptiveInferredPropertyValueWatchpointBase);
    WTF_MAKE_FAST_ALLOCATED;

public:
    AdaptiveInferredPropertyValueWatchpointBase(const ObjectPropertyCondition&);

    const ObjectPropertyCondition& key() const { return m_key; }

    void install();

    virtual ~AdaptiveInferredPropertyValueWatchpointBase() = default;

protected:
    virtual void handleFire(const FireDetail&) = 0;

private:
    class StructureWatchpoint : public Watchpoint {
    public:
        StructureWatchpoint() { }
    protected:
        void fireInternal(const FireDetail&) override;
    };
    class PropertyWatchpoint : public Watchpoint {
    public:
        PropertyWatchpoint() { }
    protected:
        void fireInternal(const FireDetail&) override;
    };

    void fire(const FireDetail&);

    ObjectPropertyCondition m_key;
    StructureWatchpoint m_structureWatchpoint;
    PropertyWatchpoint m_propertyWatchpoint;
};

} // namespace JSC
