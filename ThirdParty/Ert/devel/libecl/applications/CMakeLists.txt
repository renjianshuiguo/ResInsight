if (BUILD_APPLICATIONS)
   add_executable( sum_write sum_write.c )
   add_executable( make_grid make_grid.c )
   add_executable( grdecl_grid grdecl_grid.c )
   add_executable( summary2csv summary2csv.c )
   if (ERT_LINUX)
      add_executable( esummary.x esummary.c )
      add_executable( convert.x convert.c )
      add_executable( grdecl_test.x grdecl_test.c )
      add_executable( kw_list.x kw_list.c )
      add_executable( kw_extract.x kw_extract.c )
      add_executable( grid_info.x grid_info.c )
      add_executable( grid_dump.x grid_dump.c )
      add_executable( grid_dump_ascii.x grid_dump_ascii.c )
      add_executable( summary.x view_summary.c )
      add_executable( select_test.x select_test.c )
      add_executable( load_test.x load_test.c )
      set(program_list summary2csv esummary.x kw_extract.x grdecl_grid make_grid sum_write load_test.x grdecl_test.x grid_dump_ascii.x select_test.x grid_dump.x convert.x kw_list.x grid_info.x summary.x)
   else()
      # The stupid .x extension creates problems on windows
      add_executable( convert convert.c )
      add_executable( grdecl_test grdecl_test.c )
      add_executable( kw_list kw_list.c )
      add_executable( kw_extract kw_extract.c )
      add_executable( grid_info grid_info.c )
      add_executable( grid_dump grid_dump.c )
      add_executable( grid_dump_ascii grid_dump_ascii.c )
      add_executable( summary view_summary.c )
      add_executable( select_test select_test.c )
      add_executable( load_test load_test.c )
      set(program_list summary2csv kw_extract grdecl_grid make_grid  sum_write load_test grdecl_test grid_dump_ascii select_test grid_dump convert kw_list grid_info summary)
   endif()


   foreach(prog ${program_list})
      target_link_libraries( ${prog} ecl ert_util )
      
      #-----------------------------------------------------------------
      set (destination ${CMAKE_INSTALL_PREFIX}/bin)
      if (INSTALL_ERT)
         install(TARGETS ${prog} DESTINATION ${destination})
         if (INSTALL_GROUP)
            install(CODE "EXECUTE_PROCESS(COMMAND chgrp ${INSTALL_GROUP} ${destination}/${prog})")
            install(CODE "EXECUTE_PROCESS(COMMAND chmod g+w ${destination}/${prog})")
         endif()
      endif()
   endforeach()
endif()

if (BUILD_ENS_PLOT)
   include_directories( ${PLPLOT_HEADER} )
   add_executable( ens_plot.x ens_plot.c )
   target_link_libraries( ens_plot.x plot ecl)

   set (destination ${CMAKE_INSTALL_PREFIX}/bin)
   if (INSTALL_ERT)
      install(TARGETS ens_plot.x DESTINATION ${destination})
      if (INSTALL_GROUP)
         install(CODE "EXECUTE_PROCESS(COMMAND chgrp ${INSTALL_GROUP} ${destination}/ens_plot.x)")
         install(CODE "EXECUTE_PROCESS(COMMAND chmod g+w ${destination}/ens_plot.x)")
      endif()
   endif()
endif()



if (BUILD_ECL_SUMMARY)
   add_executable( ecl_summary view_summary.c )
   target_link_libraries( ecl_summary ecl)

   set (destination ${CMAKE_INSTALL_PREFIX}/bin)
   if (INSTALL_ERT)
      install(TARGETS ecl_summary DESTINATION ${destination})
      if (INSTALL_GROUP)
         install(CODE "EXECUTE_PROCESS(COMMAND chgrp ${INSTALL_GROUP} ${destination}/ecl_summary)")
         install(CODE "EXECUTE_PROCESS(COMMAND chmod g+w ${destination}/ecl_summary)")
      endif()
   endif()
endif()
 
