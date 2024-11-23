file(GLOB HANDLER_SRC_LIST
    "*.cpp"
)

target_sources(main PRIVATE ${HANDLER_SRC_LIST})
