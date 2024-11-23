file(GLOB LOOPER_SRC_LIST
    "*.cpp"
)

target_sources(main PRIVATE ${LOOPER_SRC_LIST})
